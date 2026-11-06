#include"State/MoveAction.h"
#include "State/Pawn.h"

using namespace State;

MoveAction::MoveAction(Pawn* pawn, Position destination) : pawn(pawn), destination(destination) {

}   

MoveAction::~MoveAction() = default;

void MoveAction::execute(GameState& state) {
    if (pawn) {
        pawn->set_position(destination);
    }
}