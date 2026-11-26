#include "state/Warrior.h"
#include "GameEngine/AttackAction.h"

using namespace state;

Warrior::Warrior(Color color, Position position) : PlayablePawn(color,position) {

}
Warrior::~Warrior() {}

void Warrior::attack_pawn(PlayablePawn* pawn, GameState& state) {
    GameEngine::AttackAction attack_action(this, pawn);
    attack_action.execute(state);
}

std::optional<Dice> Warrior::class_dice() const {
    return Dice::WARRIOR;
}