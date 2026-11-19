#include "GameEngine/RuleEngine.h"
#include "state/GameState.h"
#include "state/Action.h"
#include "state/PlayablePawn.h"
#include "state/Sorcerer.h"

#include <memory>


namespace GameEngine {

RuleEngine::RuleEngine() = default;

RuleEngine::~RuleEngine() = default;

bool RuleEngine::is_valid(state::GameState& game_state,
                           state::Action& action) {
    // Identifier le type d'action puis appliquer la règle correspondante.
    return false;
}

std::vector<std::shared_ptr<state::Action>> RuleEngine::possible_moves() {
    // Générer les actions autorisées pour le joueur courant.
    return {};
}

bool RuleEngine::can_move(state::PlayablePawn& pawn,
                          state::Position& destination,
                          state::GameState game_state) {
    // Vérifier distance, destination et nombre de déplacements.
    return false;
}

bool RuleEngine::can_attack(state::PlayablePawn& attacker,
                            state::PlayablePawn& target,
                            state::GameState& game_state) {
    // Vérifier joueur actif, adjacence et état des pions.
    return false;
}

bool RuleEngine::can_cast(state::Sorcerer& caster,
                          state::Spell& spell,
                          state::GameState& game_state) {
    // Vérifier que le lanceur peut encore lancer un sort
    // et qu’il se trouve sur une case autorisée.
    return false;
}

}