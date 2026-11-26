#include "GameEngine/Resurrection.h"
#include "state/Place.h"
#include "state/PlayablePawn.h"

namespace GameEngine {
using namespace state;

Resurrection::Resurrection(PlayablePawn* target) : Spell(), target(target) {}

Resurrection::~Resurrection() = default;

int Resurrection::get_nb_of_dice(GameState& state){return 4;}

void Resurrection::execute(GameState& state) const {
    if (target && target->get_place() == Cimetery) {
        target->set_place(Camp);
    }

    }
}