#include "state/Warrior.h"
#include "GameEngine/AttackAction.h"

using namespace state;

Warrior::Warrior(Color color, Position position) : PlayablePawn(color,position) {

}
Warrior::~Warrior() {}


std::optional<Dice> Warrior::class_dice() const {
    return Dice::WARRIOR;
}