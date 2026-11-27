#include "GameEngine/Engine.h"
#include "state/GameState.h"
#include "GameEngine/RuleEngine.h"
#include "GameEngine/Action.h"
#include "GameEngine/EndTurnAction.h"


namespace GameEngine {

Engine::Engine() : state(state::GameState()) {};

Engine::~Engine() = default;

void Engine::start_game() {
    // Implementation of starting the game
    
}

void Engine::start_turn() {
    // Implementation of starting a turn
    state.get_draw_dice().roll(3);
    state.get_current_player().get_sorcerer().reset_spell_usage();


    auto_end_if_stuck();
}

bool Engine::submit_action(Action& action) {
    // Implementation of submitting an action
     if (!rules.is_valid(state, action)) return false;
    action.execute(state);
    if (typeid(action) == typeid(EndTurnAction)) end_turn();      // EndTurnAction
    else auto_end_if_stuck();
    return true;

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
    // Implementation of auto-ending the turn if the player is stuck
    if (rules.possible_actions(state).size() == 1) end_turn();
}

state::GameState& Engine::get_state() {
    return state;
}
}
