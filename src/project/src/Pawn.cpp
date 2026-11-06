#include "State/Pawn.h"

using namespace State;

State::Pawn::Pawn(Position pos) : position(pos) {
    
}

State::Pawn::~Pawn() {}

int State::Pawn::get_distance_from(Pawn pawn) {
    return 0;
}



State::Position State::Pawn::get_position() {
    return position;
}

void State::Pawn::set_position(Position pos) {
    position = pos;
}