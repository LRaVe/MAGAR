#include "state/MoveAction.h"
#include "state/Pawn.h"
#include "state/PlayablePawn.h"
#include "state/Warrior.h"
#include "state/Sorcerer.h"
#include "state/GameState.h"
#include "state/DrawDice.h"
#include "GameEngine/RuleEngine.h"

using namespace state;

MoveAction::MoveAction(Pawn* pawn, Position destination)
    : pawn(pawn), destination(destination)
{
}

MoveAction::~MoveAction() = default;

static bool areHexAdjacent(const Position& p1, const Position& p2)
{
    return p1.is_adjacent_to(p2);
}

static Dice get_required_die_for(Pawn* pawn)
{
    if (dynamic_cast<Warrior*>(pawn) != nullptr) return WARRIOR;
    if (dynamic_cast<Sorcerer*>(pawn) != nullptr) return SORCERER;
    return TRISKELL; // ou une valeur par défaut si on utilise pas MoveAction pour bouger le dragon
}

bool MoveAction::can_apply(GameState& state) const
{

    if (!pawn) {
        return false;
    }


    auto* playable = dynamic_cast<PlayablePawn*>(pawn);
    if (playable && playable->get_place() != Place::Arena) {
        return false;
    }

    // Vérification de la distance hexagonale
    if (!areHexAdjacent(pawn->get_position(), destination)) {
        return false;
    }

    // ce dé est-il disponible dans la réserve
    Dice required_die = get_required_die_for(pawn);
    if (!state.get_draw_dice().has_dice(required_die)) {
        return false;
    }

    return true;
}

void MoveAction::execute(GameState& state)
{
    // On valide d'abord avec can_apply
    if (can_apply(state))
    {
        //On consomme le dé
        Dice required_die = get_required_die_for(pawn);
        state.get_draw_dice().consume_dice(required_die);

        //On déplace le pion
        pawn->set_position(destination);
    }
}

bool MoveAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
    return false;
}