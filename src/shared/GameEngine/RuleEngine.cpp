#include "GameEngine/RuleEngine.h"
#include "state/GameState.h"
#include "state/PlayablePawn.h"
#include "state/Sorcerer.h"
#include "state/Warrior.h"
#include "state/Player.h"
#include "state/Board.h"
#include "state/Dragon.h"
#include "GameEngine/Action.h"
#include "GameEngine/AttackAction.h"
#include "GameEngine/MoveAction.h"
#include "GameEngine/HealAction.h"
#include "GameEngine/ReviveAction.h"
#include <memory>
#include <array>

#include "CastAction.h"

namespace GameEngine {

RuleEngine::RuleEngine() = default;

RuleEngine::~RuleEngine() = default;

std::optional<std::array<state::Position, 4>> RuleEngine::camp_entries_for(
    state::Color color)
{
    switch (color) {
    case state::Color::Red:
        return std::array{
            state::Position(-4, -1),
            state::Position(-3, -2),
            state::Position(-2, -3),
            state::Position(-1, -4)
        };
    case state::Color::Blue:
        return std::array{
            state::Position(5, -4),
            state::Position(5, -3),
            state::Position(5, -2),
            state::Position(5, -1)
        };
    case state::Color::Green:
        return std::array{
            state::Position(-5, 1),
            state::Position(-5, 2),
            state::Position(-5, 3),
            state::Position(-5, 4)
        };
    case state::Color::Yellow:
        return std::array{
            state::Position(1, 4),
            state::Position(2, 3),
            state::Position(3, 2),
            state::Position(4, 1)
        };
    }
    return std::nullopt;
}

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
        if (pawn->get_place() == state::Place::Camp) {
            const auto entries = camp_entries_for(pawn->get_color());
            if (entries) {
                for (const state::Position& entry : *entries) {
                    if (can_move(*pawn, entry, game_state)) {
                        actions.push_back(
                            std::make_shared<MoveAction>(pawn, entry));
                    }
                }
            }
            continue;
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
        if (game_state.has_attacked_this_turn()) {
            continue;
        }

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

    if (game_state.get_draw_dice().has_dice(state::TRISKELL)) {
        state::Dragon& dragon = game_state.get_dragon();
        for (const state::Position& destination : dragon.get_position().neighbors()) {
            auto action = std::make_shared<MoveAction>(&dragon, destination);
            if (action->can_apply(game_state)) {
                actions.push_back(action);
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
    if (game_state.has_attacked_this_turn()) {
        return false;
    }
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
