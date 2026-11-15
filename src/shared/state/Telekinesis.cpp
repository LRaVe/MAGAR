#include "state/Telekinesis.h"
#include "state/GameState.h"

using namespace state;

Telekinesis::Telekinesis(Position destination) : Spell(), destination(destination) {}

void Telekinesis::execute(GameState& state) const {
    state.get_stone().set_position(destination);
}