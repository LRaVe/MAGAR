#include "GameEngine/AttackAction.h"
#include "state/GameState.h"
#include "state/PlayablePawn.h"
#include "state/AttackDice.h"
#include "GameEngine/RuleEngine.h"
#include <cmath>
#include <iostream>

namespace GameEngine {
using namespace state;

AttackAction::AttackAction(PlayablePawn* attacker, PlayablePawn* target)
    : attacker(attacker), target(target)
{
}

AttackAction::~AttackAction() = default;

// Vérification de la cible
bool AttackAction::is_enemy_valid() const
{
    // Les deux pions doivent exister
    if (!attacker || !target) {
        return false;
    }

    // On ne peut pas s'attaquer soi-même
    if (attacker == target) {
        return false;
    }

    // On ne peut pas attaquer un pion de sa propre équipe
    if (attacker->get_color() == target->get_color()) {
        return false;
    }

    return true;
}

// Vérification que les deux combattants sont sur le terrain
bool AttackAction::are_pawns_in_arena() const
{
    if (!attacker || !target) {
        return false;
    }

    return (attacker->get_place() == Place::Arena &&
            target->get_place() == Place::Arena);
}

// Vérification de la portée (adjacence hexagonale)
bool AttackAction::is_target_adjacent() const
{
    if (!attacker || !target) {
        return false;
    }

    return attacker->get_position().is_adjacent_to(target->get_position());
}

    int AttackAction::countSuccesses(const std::vector<bool>& draw)
{
    int count = 0;
    for (bool hit : draw)
    {
        if (hit)
        {
            count++;
        }
    }
    return count;
}

bool AttackAction::can_apply() const
{
    return is_enemy_valid()
        && are_pawns_in_arena()
        && is_target_adjacent();
}

void AttackAction::execute(GameState&)
{
    // Combat seulement si can_apply est valide
    if (!can_apply()) {
        std::cerr << "AttackAction Erreur : Attaque illégale !" << std::endl;
        return;
    }

    // Gestion du combat
    AttackDice dice;

    int attackerAttackVal = attacker->get_attack();
    dice.roll(attackerAttackVal);
    int attackerSuccesses = countSuccesses(dice.get_draw());

    int targetAttackVal = target->get_attack();
    dice.roll(targetAttackVal);
    int targetSuccesses = countSuccesses(dice.get_draw());

    std::cout << "[Combat] Attaquant (" << attackerAttackVal << " dés) -> " << attackerSuccesses << " succès." << std::endl;
    std::cout << "[Combat] Cible (" << targetAttackVal << " dés) -> " << targetSuccesses << " succès." << std::endl;

    // Résolution du combat
    resolve_combat(attackerSuccesses, targetSuccesses);
}

void AttackAction::resolve_combat(int attacker_successes, int target_successes)
{
    if (attacker_successes > target_successes)
    {
        std::cout << "[Combat] L'Attaquant gagne, la cible est envoyée à l'hôpital." << std::endl;
        target->set_place(Hospital);
    }
    else if (target_successes > attacker_successes)
    {
        std::cout << "[Combat] La Cible gagne, l'attaquant est envoyé à l'hôpital." << std::endl;
        attacker->set_place(Hospital);
    }
    else
    {
        std::cout << "[Combat] Égalité ! (" << attacker_successes << "-" << target_successes << "). Rien ne se passe." << std::endl;
    }
}

bool AttackAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
    return can_apply();
}

}