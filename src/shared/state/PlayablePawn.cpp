#include "state/PlayablePawn.h"
using namespace state;


PlayablePawn::PlayablePawn(Color color, Position position) : Pawn(position), color(color) {
    attack = 0;
    is_wolf = false;
    place = Camp;
    nb_moves = 0;
}

PlayablePawn::~PlayablePawn() = default;

void PlayablePawn::set_attack(int value) {
    attack = value;
}

int PlayablePawn::get_attack() const {
    return attack;
}

void PlayablePawn::set_place(Place new_place) {
    place = new_place;
}

Place PlayablePawn::get_place() {
    return place;
}