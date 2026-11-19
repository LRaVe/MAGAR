#include "state/Pawn.h"
using namespace state;

state::Pawn::Pawn(Position pos) : position(pos) {
    
}

state::Pawn::~Pawn() {}

state::Position state::Pawn::get_position() const {
    return position;
}

int state::Pawn::get_distance_from(const Pawn& pawn) const {
    const Position other_position = pawn.get_position();
    return position.distance_to(other_position);
}


void state::Pawn::set_position(Position pos) {
    position = pos;
}