#include "GameEngine/TurnManager.h"
#include "state/GameState.h"
#include "state/Player.h"

namespace GameEngine {

TurnManager::TurnManager()
    : currentTurn(0), currentPhase(Dice) {}

TurnManager::~TurnManager() = default;

Phase TurnManager::get_phase() {
    return currentPhase;
}

void TurnManager::set_phase(Phase phase) {
    currentPhase = phase;
}

void TurnManager::next_turn(state::GameState& state) {
    state.next_turn();
    currentTurn = state.get_turn();
    currentPhase = Dice;
}

state::Player& TurnManager::current_player(state::GameState& state) {
    return state.get_current_player();
}

}