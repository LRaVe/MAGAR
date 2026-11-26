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

#include <memory>


namespace GameEngine {

RuleEngine::RuleEngine() = default;

RuleEngine::~RuleEngine() = default;

bool RuleEngine::is_valid(state::GameState& game_state,
                          Action& action) {
    // Identifier le type d'action puis appliquer la règle correspondante.
    return action.validate(*this, game_state);
}

std::vector<std::shared_ptr<Action>> RuleEngine::possible_actions(
    state::GameState& game_state) {
    std::vector<std::shared_ptr<Action>> actions;

    auto draw = game_state.get_draw_dice();

    state::Player& current_player = game_state.get_current_player();
    state::PlayablePawn* pawns[] = {
        &current_player.get_warrior(),
        &current_player.get_sorcerer()
    };

    for (state::PlayablePawn* pawn : pawns) {
        if (pawn->get_place() != state::Place::Arena) {
            continue;
        }

        const state::Position origin = pawn->get_position();
        for (const state::Position& destination : origin.neighbors()) {
            if (can_move(*pawn, destination, game_state)) {
                actions.push_back(
                    std::make_shared<MoveAction>(pawn, destination));
            }
        }

        for (state::Player& player : game_state.get_players()) {
            if (player.getColor() == current_player.getColor()) {
                continue;
            }

            state::PlayablePawn* targets[] = {
                &player.get_warrior(),
                &player.get_sorcerer()
            };
            for (state::PlayablePawn* target : targets) {
                if (target->get_place() == state::Place::Arena
                    && can_attack(*pawn, *target, game_state)) {
                    actions.push_back(
                        std::make_shared<AttackAction>(pawn, target));
                }
            }
        }
    }

    return actions;
}

bool RuleEngine::can_move(state::PlayablePawn& pawn,
                          const state::Position& destination,
                          state::GameState& game_state) {
    if (pawn.get_place() != state::Place::Arena
        || !pawn.get_position().is_adjacent_to(destination)
        || !destination.is_in_radius(5)) {
        return false;
    }

    return game_state.get_board().get_tile_from(destination) != nullptr;
}

bool RuleEngine::can_attack(state::PlayablePawn& attacker,
                            state::PlayablePawn& target,
                            state::GameState& game_state) {
    if (attacker.get_place() != state::Place::Arena
        || target.get_place() != state::Place::Arena) {
        return false;
    }
    if (&attacker == &target
        || attacker.get_color() == target.get_color()) {
        return false;
    }
    return attacker.get_position().is_adjacent_to(target.get_position());
}

bool RuleEngine::can_cast(state::Sorcerer& caster,
                          Spell& spell,
                          state::GameState& game_state) {
    // Vérifier que le lanceur peut encore lancer un sort
    // et qu’il se trouve sur une case autorisée.
    return false;
}

}