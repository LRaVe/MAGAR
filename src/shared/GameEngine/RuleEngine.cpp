#include "GameEngine/RuleEngine.h"
#include "state/GameState.h"
#include "state/PlayablePawn.h"
#include "state/Sorcerer.h"
#include "state/Warrior.h"
#include "state/Player.h"
#include "state/Board.h"
#include "GameEngine/Action.h"
#include "GameEngine/AttackAction.h"
#include "GameEngine/MoveAction.h"
#include "GameEngine/HealAction.h"
#include "GameEngine/ReviveAction.h"

#include <memory>

#include "CastAction.h"


namespace GameEngine {

RuleEngine::RuleEngine() = default;

RuleEngine::~RuleEngine() = default;

bool RuleEngine::is_valid(state::GameState& game_state, Action& action) {
    // Identifier le type d'action puis appliquer la règle correspondante.
    return action.validate(*this, game_state);
}

std::vector<std::shared_ptr<Action>> RuleEngine::possible_actions(state::GameState& game_state) {
    std::vector<std::shared_ptr<Action>> actions;

    const auto&  draw = game_state.get_draw_dice().get_draw();

    state::Player& current_player = game_state.get_current_player();
    state::PlayablePawn* pawns[] = {
        &current_player.get_warrior(),
        &current_player.get_sorcerer()
    };

    for (state::PlayablePawn* pawn : pawns) {
        // verification soin (Hospital -> Camp)
        if (pawn->get_place() == state::Place::Hospital && can_heal(*pawn, game_state)) {
            actions.push_back(std::make_shared<HealAction>(pawn, draw));
        }
        // verification resurrection (Cimetery -> Camp)
        if (pawn->get_place() == state::Place::Cimetery && can_revive(*pawn, game_state)) {
            actions.push_back(std::make_shared<ReviveAction>(pawn, draw));
        }
        // combat et déplacement
        if (pawn->get_place() != state::Place::Arena) {
            continue; // si pawn n'est pas dans Arena, il ne peut ni bouger ni attaquer
        }

        const state::Position origin = pawn->get_position();
        for (const state::Position& destination : origin.neighbors()) {
            if (can_move(*pawn, destination, game_state)) {
                actions.push_back(std::make_shared<MoveAction>(pawn, destination));
            }
        }
        // attaques possibles
        for (state::Player& player : game_state.get_players()) {
            if (player.getColor() == current_player.getColor()) {
                continue; // pas d'attaque sur soi-même
            }

            state::PlayablePawn* targets[] = {
                &player.get_warrior(),
                &player.get_sorcerer()
            };
            for (state::PlayablePawn* target : targets) {
                if (target->get_place() == state::Place::Arena
                    && can_attack(*pawn, *target, game_state)) {
                    actions.push_back(std::make_shared<AttackAction>(pawn, target));
                }
            }
        }
    }

    return actions;
}

bool RuleEngine::can_move(state::PlayablePawn& pawn,
                              const state::Position& destination,
                              state::GameState& game_state) {
    MoveAction action(&pawn, destination);
    return action.can_apply(game_state);
}

bool RuleEngine::can_attack(state::PlayablePawn& attacker,
                                state::PlayablePawn& target,
                                state::GameState& game_state)
{
    AttackAction action(&attacker, &target);
    return action.can_apply(); // Délégation complète et sans doublon !
}

bool RuleEngine::can_cast(state::Sorcerer& caster,
                          Spell& spell,
                          state::GameState& game_state) {
    // le sorcier doit être vivant sur le plateau
    if (caster.get_place() != state::Place::Arena) {
        return false;
    }

    CastAction action(&caster, &spell);
    return action.isOnStarTile(game_state);
}

bool RuleEngine::can_heal(state::PlayablePawn& pawn, state::GameState& game_state)
{
    HealAction action(&pawn, game_state.get_draw_dice().get_draw());
    return action.can_apply();
}

bool RuleEngine::can_revive(state::PlayablePawn& pawn, state::GameState& game_state)
{
    ReviveAction action(&pawn, game_state.get_draw_dice().get_draw());
    return action.can_apply();
}
}
