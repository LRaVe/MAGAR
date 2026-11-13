#include "State/Warrior.h"
#include "State/AttackAction.h"

using namespace State;

Warrior::Warrior(Color color, Position position) : PlayablePawn(color,position) {

}
Warrior::~Warrior() {}

void Warrior::attack_pawn(PlayablePawn* pawn, GameState& state) {
    AttackAction attack_action(this, pawn);
    attack_action.execute(state);
}
