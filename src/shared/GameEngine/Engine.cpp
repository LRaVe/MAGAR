#include "GameEngine/Engine.h"
#include "state/GameState.h"
#include "GameEngine/RuleEngine.h"
#include "GameEngine/Action.h"
#include "GameEngine/TurnManager.h"
#include "GameEngine/EndTurnAction.h"


namespace GameEngine {

Engine::Engine(state::GameState& state) : state(state) {

}

Engine::~Engine() = default;


void Engine::start_game() {
    // Implementation of starting the game
    
}

void Engine::start_turn() {
    state.get_draw_dice().roll(3);
    state.get_current_player().get_sorcerer().reset_spell_usage();
}

bool Engine::submit_action(Action& action) {
    if (!rules.is_valid(state, action)) return false;
    action.execute(state);
    if (typeid(action) == typeid(EndTurnAction)) end_turn();
    return true;

}

std::vector<std::shared_ptr<Action>> Engine::possible_actions() {
    return rules.possible_actions(state);
}

void Engine::end_turn() {
    state.next_turn();
    start_turn();

}

bool Engine::is_game_over() {
    // Implementation of checking if the game is over
    return false; // Placeholder return value
}

void Engine::auto_end_if_stuck() {
    if (rules.possible_actions(state).size() == 1) end_turn();
}

}