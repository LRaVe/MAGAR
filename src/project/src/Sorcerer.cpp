#include "State/Sorcerer.h"
#include "../include/State/Sorcerer.h"

using namespace State;

Sorcerer::Sorcerer(Color color, Position position) : PlayablePawn(color,position) {

}

Sorcerer::~Sorcerer() {}

void Sorcerer::set_place(Place place) {
    this->place = place;
}

Place Sorcerer::get_place() {
    return this->place;
}



void Sorcerer::cast_spell(int ) {
    
}