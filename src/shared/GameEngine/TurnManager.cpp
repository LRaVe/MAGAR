#include "GameEngine/TurnManager.h"
#include "state/GameState.h"
#include "state/Player.h"

namespace GameEngine {

TurnManager::TurnManager()
    : currentTurn(0) {}

TurnManager::~TurnManager() = default;




void TurnManager::next_turn(state::GameState& state) {
    state.next_turn();
    currentTurn = state.get_turn();
    
}

state::Player& TurnManager::current_player(state::GameState& state) {
    return state.get_current_player();
}

}