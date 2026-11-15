#include "state/Heal.h"
#include "state/Place.h"
#include "state/PlayablePawn.h"

using namespace state;

Heal::Heal(PlayablePawn* target) : Spell(), target(target) {}

Heal::~Heal() {}

void Heal::execute(GameState& state) const {
    if (target && target->get_place() == Hospital) {
        target->set_place(Camp);
    }
}