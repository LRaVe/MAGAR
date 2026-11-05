#include "State/PlayablePawn.h"
using namespace State;


PlayablePawn::PlayablePawn(Color color, Position position) : Pawn(position), color(color) {
    attack = 0;
    is_wolf = false;
    place = Camp;
    nb_moves = 0;
}

PlayablePawn::~PlayablePawn() = default;

void PlayablePawn::attack_pawn(Pawn pawn) {

}

void PlayablePawn::move(Position position) {

}