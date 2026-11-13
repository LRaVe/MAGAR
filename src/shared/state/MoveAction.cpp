#include"state/MoveAction.h"
#include "state/Pawn.h"

using namespace state;

MoveAction::MoveAction(Pawn* pawn, Position destination) : pawn(pawn), destination(destination) {

}   

MoveAction::~MoveAction() = default;

void MoveAction::execute(GameState& state) {
    if (pawn) {
        pawn->set_position(destination);
    }
}