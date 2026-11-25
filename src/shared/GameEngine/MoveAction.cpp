#include "GameEngine/MoveAction.h"
#include "state/Pawn.h"
#include "state/PlayablePawn.h"
#include "state/GameState.h"
#include "state/Board.h"
#include "state/DrawDice.h"
#include "GameEngine/RuleEngine.h"

namespace GameEngine {
using namespace state;

MoveAction::MoveAction(Pawn* pawn, Position destination)
    : pawn(pawn), destination(destination)
{
}

MoveAction::~MoveAction() = default;

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
    if (playable && playable->get_place() != Place::Arena) {
        return false; // pawn doit être dans Arena
    }

    return true;
}

// 2. Vérification spatiale (Adjacence + Rayon 5 + Existence de la case)
bool MoveAction::is_destination_valid(GameState& state) const
{
    if (!pawn) {
        return false;
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
        pawn->set_position(destination);
    }
}

bool MoveAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
    return can_apply(state);
}

} // namespace GameEngine