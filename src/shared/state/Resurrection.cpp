#include "state/Resurrection.h"
#include "state/Place.h"
#include "state/PlayablePawn.h"

using namespace state;

Resurrection::Resurrection(PlayablePawn* target) : Spell(), target(target) {}

void Resurrection::execute(GameState& state) {
    if (target && target->get_place() == Cimetery) {
        target->set_place(Camp);
    }
}