#include "state/PlayablePawn.h"
#include <optional>
#include "../../src/shared/state/Dice.h"
using namespace state;


PlayablePawn::PlayablePawn(Color color, Position position) : Pawn(position), color(color) {
    attack = 0;
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

int PlayablePawn::get_nb_moves() {
    return nb_moves;
}

Color PlayablePawn::get_color() const {
    return color;
}

std::optional<Dice> PlayablePawn::class_dice() const {
    return std::nullopt;
}

PlayablePawn* PlayablePawn::as_playable() {
    return this;
}