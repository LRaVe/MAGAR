#include "GameEngine/GameEngine.h"
#include "state/GameState.h"
#include "state/Action.h"


namespace GameEngine {

GameEngine::GameEngine(State::GameState& state) : state(state) {

}

GameEngine::~GameEngine() = default;


void GameEngine::start_game() {
    // Implementation of starting the game
}

void GameEngine::start_turn() {
    // Implementation of starting a turn
}

void GameEngine::submit_action(State::Action& action) {
    // Implementation of submitting an action
}

void GameEngine::end_turn() {
    // Implementation of ending a turn
}

bool GameEngine::is_game_over() {
    // Implementation of checking if the game is over
    return false; // Placeholder return value
}

}