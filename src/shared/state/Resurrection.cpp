#include "state/Resurrection.h"
#include "state/Place.h"
#include "state/PlayablePawn.h"

using namespace state;

Resurrection::Resurrection(PlayablePawn* target) : Spell(), target(target) {}

int Resurrection::get_nb_of_dice(GameState& state){return 4;}

void Resurrection::execute(GameState& state) const {
    if (target && target->get_place() == Cimetery) {
        target->set_place(Camp);
    }
}