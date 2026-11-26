#include "state/Sorcerer.h"
#include "GameEngine/Spell.h"
#include "GameEngine/AttackAction.h"

using namespace state;

Sorcerer::Sorcerer(Color color, Position position) 
    : PlayablePawn(color,position),
    can_spell(true) {
}

Sorcerer::~Sorcerer() {}


bool Sorcerer::cast_spell(const GameEngine::Spell& spell, GameState& state) {
    if (!can_spell) {
        return false;
    }
    spell.execute(state);
    can_spell=false;

    return true;
}

void Sorcerer::attack_pawn(PlayablePawn* pawn, GameState& state) { 
    GameEngine::AttackAction attack_action(this, pawn);
    attack_action.execute(state);
}

void Sorcerer::reset_spell_usage() {
    can_spell=true;
}

std::optional<Dice> Sorcerer::class_dice() const {
    return Dice::SORCERER;
}