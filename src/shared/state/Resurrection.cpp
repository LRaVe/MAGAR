#include "state/Resurrection.h"
#include "state/Place.h"
#include "state/PlayablePawn.h"

using namespace state;

Resurrection::Resurrection(PlayablePawn* target) : Spell(), target(target) {}

void Resurrection::execute(GameState& state) {
    target->set_place(Place::Camp);
}