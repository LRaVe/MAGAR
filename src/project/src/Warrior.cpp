#include "State/Warrior.h"
#include "../include/State/Warrior.h"

using namespace State;

Warrior::Warrior(Color color, Position position) : PlayablePawn(color,position) {

}

Warrior::~Warrior() {}

void Warrior::set_place(Place place) {
    this->place = place;
}

Place Warrior::get_place() {
    return this->place;
}

