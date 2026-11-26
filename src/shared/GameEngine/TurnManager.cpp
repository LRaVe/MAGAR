#include "GameEngine/TurnManager.h"
#include "state/GameState.h"

namespace GameEngine {

TurnManager::TurnManager()
    : currentTurn(0) {}

TurnManager::~TurnManager() = default;



void TurnManager::next_turn(state::GameState& state) {
    state.next_turn();
    currentTurn = state.get_turn();
    
}
}