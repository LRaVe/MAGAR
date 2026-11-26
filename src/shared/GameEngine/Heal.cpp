#include "GameEngine/Heal.h"
#include "state/Place.h"
#include "state/PlayablePawn.h"

namespace GameEngine {
using namespace state;

Heal::Heal(PlayablePawn* target) : Spell(), target(target) {}

Heal::~Heal() {}

int Heal::get_nb_of_dice(GameState& state)
{
    return 2;
}

void Heal::execute(GameState& state) const {
    if (target && target->get_place() == Hospital) {
        target->set_place(Camp);
    }

    }
}