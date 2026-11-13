#include "State/Telekinesis.h"
#include "State/GameState.h"

using namespace State;

Telekinesis::Telekinesis(Position destination) : Spell(), destination(destination) {}

void Telekinesis::execute(GameState& state) {
    state.get_stone().set_position(destination);
}