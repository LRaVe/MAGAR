#include "state/Pawn.h"

using namespace state;

state::Pawn::Pawn(Position pos) : position(pos) {
    
}

state::Pawn::~Pawn() {}

int state::Pawn::get_distance_from(Pawn pawn) {
    return 0;
}



state::Position state::Pawn::get_position() {
    return position;
}

void state::Pawn::set_position(Position pos) {
    position = pos;
}