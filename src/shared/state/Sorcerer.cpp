#include "state/Sorcerer.h"
#include "GameEngine/Spell.h"
#include "GameEngine/AttackAction.h"

using namespace state;

Sorcerer::Sorcerer(Color color, Position position) 
    : PlayablePawn(color,position),
    can_spell(true) {
}

Sorcerer::~Sorcerer() {}




void Sorcerer::reset_spell_usage() {
    can_spell=true;
}

std::optional<Dice> Sorcerer::class_dice() const {
    return Dice::SORCERER;
}