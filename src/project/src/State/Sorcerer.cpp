#include "State/Sorcerer.h"
#include "State/Spell.h"
#include "State/AttackAction.h"

using namespace State;

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