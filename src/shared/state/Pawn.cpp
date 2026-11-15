#include "state/Pawn.h"
#include <cstdlib>

namespace {

state::Position subtract(
    const state::Pawn& pawn1,
    const state::Pawn& pawn2) {
    const state::Position pos1=pawn1.get_position();
    const state::Position pos2=pawn2.get_position();
    return state::Position(pos1.q-pos2.q,pos1.r-pos2.r);
}

int length(const state::Position& pos) {
    return (std::abs(pos.q) + std::abs(pos.r) + std::abs(pos.s())) / 2;}
}


using namespace state;

state::Pawn::Pawn(Position pos) : position(pos) {
    
}

state::Pawn::~Pawn() {}

state::Position state::Pawn::get_position() const {
    return position;
}

int state::Pawn::get_distance_from(const Pawn& pawn) const {
    const Position other_position = pawn.get_position();
    return length(subtract(*this,pawn));
}


void state::Pawn::set_position(Position pos) {
    position = pos;
}