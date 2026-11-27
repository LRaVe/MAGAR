#include "GameEngine/MoveAction.h"
#include "state/Pawn.h"
#include "state/PlayablePawn.h"
#include "state/GameState.h"
#include "state/Board.h"
#include "state/CenterTile.h"
#include "state/DrawDice.h"
#include "state/Dragon.h"
#include "state/NestTile.h"
#include "state/Player.h"
#include "GameEngine/RuleEngine.h"

#include <algorithm>

namespace GameEngine {
using namespace state;

namespace {

bool same_position(const Position& lhs, const Position& rhs)
{
    return lhs.q == rhs.q && lhs.r == rhs.r;
}

bool occupied_by_other_pawn(
    Pawn* moving_pawn,
    const Position& destination,
    GameState& state)
{
    for (Player& player : state.get_players()) {
        PlayablePawn* pawns[] = {
            &player.get_warrior(),
            &player.get_sorcerer()
        };
        for (PlayablePawn* other : pawns) {
            if (other != moving_pawn
                && other->get_place() == Place::Arena
                && same_position(other->get_position(), destination)) {
                return true;
            }
        }
    }

    Dragon& dragon = state.get_dragon();
    return &dragon != moving_pawn
        && same_position(dragon.get_position(), destination);
}

}

MoveAction::MoveAction(Pawn* pawn, Position destination)
    : pawn(pawn), destination(destination)
{
}

MoveAction::~MoveAction() = default;

Pawn* MoveAction::get_pawn() const
{
    return pawn;
}

Position MoveAction::get_destination() const
{
    return destination;
}

// identifier le dé nécessaire
static Dice get_required_die_for(Pawn* pawn) {
    if (auto* playable = pawn->as_playable()) {
        if (auto die = playable->class_dice()) {
            return *die;
        }
    }
    return TRISKELL; // Pions non jouables (Dragon) ou par défaut
}

// méthodes de verification

// 1. Vérification du pion
bool MoveAction::is_pawn_eligible() const
{
    if (!pawn) {
        return false;
    }

    auto* playable = pawn->as_playable();
    if (!playable && !dynamic_cast<Dragon*>(pawn)) {
        return false;
    }
    if (playable
        && playable->get_place() != Place::Arena
        && playable->get_place() != Place::Camp) {
        return false;
    }

    return true;
}

// 2. Vérification spatiale (Adjacence + Rayon 5 + Existence de la case)
bool MoveAction::is_destination_valid(GameState& state) const
{
    if (!pawn) {
        return false;
    }

    if (auto* playable = pawn->as_playable()) {
        if (playable->get_place() == Place::Camp) {
            const auto entries =
                RuleEngine::camp_entries_for(playable->get_color());
            const bool is_entry = entries && std::any_of(
                entries->begin(),
                entries->end(),
                [this](const Position& entry) {
                    return same_position(destination, entry);
                });
            return is_entry
                && destination.is_in_radius(5)
                && state.get_board().get_tile_from(destination) != nullptr
                && !occupied_by_other_pawn(pawn, destination, state);
        }
        if (playable->get_place() != Place::Arena) {
            return false;
        }
    }

    // Adjacence hexagonale
    if (!pawn->get_position().is_adjacent_to(destination)) {
        return false;
    }

    // Limites du plateau (ne doit pas sortir du rayon 5)
    if (!destination.is_in_radius(5)) {
        return false;
    }

    // La tuile doit réellement exister sur le plateau
    if (state.get_board().get_tile_from(destination) == nullptr) {
        return false;
    }

    if (pawn->as_playable()
        && occupied_by_other_pawn(pawn, destination, state)) {
        return false;
    }

    return true;
}

// 3. Vérification de la réserve de dés
bool MoveAction::has_required_die(GameState& state) const
{
    Dice required_die = get_required_die_for(pawn);
    return state.get_draw_dice().has_dice(required_die);
}


bool MoveAction::can_apply(GameState& state) const
{
    return is_pawn_eligible()
        && is_destination_valid(state)
        && has_required_die(state);
}

void MoveAction::execute(GameState& state)
{
    // On se déplace si can_apply (les conditions) sont valides
    if (can_apply(state))
    {
        // 1. Consommation du dé dans la boîte de dés
        Dice required_die = get_required_die_for(pawn);
        state.get_draw_dice().consume_dice(required_die);

        // 2. Déplacement du pion
        auto* playable = pawn->as_playable();
        const bool entering_arena =
            playable && playable->get_place() == Place::Camp;
        const bool dragon_move = dynamic_cast<Dragon*>(pawn) != nullptr;
        pawn->set_position(destination);

        if (entering_arena) {
            playable->set_place(Place::Arena);
        }

        if (dragon_move) {
            const auto tile = state.get_board().get_tile_from(destination);
            const bool in_nest =
                std::dynamic_pointer_cast<NestTile>(tile) != nullptr
                || std::dynamic_pointer_cast<CenterTile>(tile) != nullptr;
            const Place destination_place = in_nest ? Place::Cimetery : Place::Hospital;

            for (Player& player : state.get_players()) {
                PlayablePawn* pawns[] = {
                    &player.get_warrior(),
                    &player.get_sorcerer()
                };
                for (PlayablePawn* target : pawns) {
                    if (target->get_place() == Place::Arena
                        && same_position(target->get_position(), destination)) {
                        target->set_place(destination_place);
                    }
                }
            }
        }
    }
}

bool MoveAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
    (void)rules;
    return can_apply(state);
}

} // namespace GameEngine