#include "State/Resurrection.h"
#include "State/Place.h"
#include "State/PlayablePawn.h"

using namespace State;

Resurrection::Resurrection(PlayablePawn* target) : Spell() {
    this->target=target;
}

void Resurrection::execute(GameState& state) {
    target->set_place(Place::Camp);
}