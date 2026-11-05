#include "State/Pawn.h"

using namespace State;

State::Pawn::Pawn(Position pos) : position(pos) {
    
}

State::Pawn::~Pawn() {}

int State::Pawn::get_distance_from(Pawn pawn) {
}

void State::Pawn::move(Position new_position) {
    position=new_position;
}

State::Position State::Pawn::get_position() {
    return position;
}

void State::Pawn::setPosition(const Position& pos) {
    position = pos;
}