#include "state/Sorcerer.h"
#include "state/Spell.h"
#include "state/AttackAction.h"

using namespace state;

Sorcerer::Sorcerer(Color color, Position position) : PlayablePawn(color,position) {

}

Sorcerer::~Sorcerer() {}


void Sorcerer::cast_spell(Spell spell, GameState& state) {
    spell.execute(state);
}


void Sorcerer::attack_pawn(PlayablePawn* pawn, GameState& state) { 
    AttackAction attack_action(this, pawn);
    attack_action.execute(state);
}