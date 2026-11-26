#include "GameEngine/GameEngine.h"
#include "state/GameState.h"
#include "GameEngine/RuleEngine.h"
#include "GameEngine/Action.h"
#include "GameEngine/TurnManager.h"


namespace GameEngine {

GameEngine::GameEngine(state::GameState& state) : state(state) {

}

GameEngine::~GameEngine() = default;


void GameEngine::start_game() {
    // Implementation of starting the game
    
}

void GameEngine::start_turn() {
    // Implementation of starting a turn
    state.get_draw_dice().roll(3);
    

      
}

void GameEngine::submit_action(Action& action) {
    // Implementation of submitting an action
    if(!rules.is_valid(state,action)){
        return;
    }

}

void GameEngine::end_turn() {
    turn_manager.next_turn(state);
}

bool GameEngine::is_game_over() {
    // Implementation of checking if the game is over
    return false; // Placeholder return value
}

}