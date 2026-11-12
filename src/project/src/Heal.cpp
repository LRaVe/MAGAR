#include "State/Heal.h"
#include "State/Place.h"
#include "State/PlayablePawn.h"

using namespace State;

Heal::Heal(PlayablePawn* target) {
    this->target = target; 
}

void Heal::execute(GameState& state) {
    target->set_place(Place::Camp);
}