#include "State/Pawn.h"

using namespace State;

Pawn::Pawn(Position position) : position(position) {

}

Position Pawn::get_position() {
    return position;
}

void Pawn::move(Position new_position){
    position = new_position;
}

int Pawn::get_distance_from(Pawn pawn) {
    Position pos = pawn.get_position();
    return pos.q;
}

