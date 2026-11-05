#include "State/AttackAction.h"
#include "State/GameState.h"
#include "State/PlayablePawn.h"
#include "State/AttackDice.h"
#include <cmath>
#include <algorithm>
#include <iostream>


State::AttackAction::AttackAction(PlayablePawn* attacker, PlayablePawn* target) : attacker(attacker), target(target) {

}

namespace State //pas sûr du bail bro
{
    static bool areHexAdjacent(Position& p1, Position& p2) // à supprimer potentiellement, si redondante
    {
        int dq = std::abs(p1.q - p2.q);
        int dr = std::abs(p1.r - p2.r);
        int ds = std::abs(p1.s() - p2.s());

        //Distance hexagonale en coordonnés cubiques
        int distance = (dq + dr + ds) / 2;
        return distance == 1;
    }

    static int countSuccesses(const std::vector<bool>& draw)
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
}
void State::AttackAction::execute(GameState& state){
    //verification préliminaires : l'un des deux est invalide ou le pion s'attaque lui même
    if (!attacker || !target)
    {
        std::cerr << "AttackAction Erreur : Attaquant ou cible invalide." << std::endl;
        return;
    }
    if (attacker == target)
    {
        std::cerr << "AttackAction Erreur : un pion ne peut pas s'attaquer lui même" << std::endl;
        return;
    }

    Position posAttacker = attacker->get_position();
    Position posTarget = target->get_position();

    if (!areHexAdjacent(posAttacker,posTarget))
    {
        std::cout << "AttackAction Erreur : la cible n'est pas sur une case voisine" << std::endl;
        return;
    }

    //gestion du combat
    AttackDice dice;

    int attackerAttackVal = attacker -> get_attack(); //valeur entre 0 et 4
    dice.roll(attackerAttackVal);
    int attackerSuccesses = countSuccesses(dice.get_draw());

    int targetAttackVal = target -> get_attack();
    dice.roll(targetAttackVal);
    int targetSuccesses = countSuccesses(dice.get_draw());

    std::cout << "[Combat] Attaquant (" << attackerAttackVal<<"des) ->"<<attackerSuccesses<<"succes."<<std::endl;
    std::cout << "[Combat] Cible (" << targetAttackVal<<"des) ->"<<targetSuccesses<<"succes."<<std::endl;

    //résolution du combat

    if (attackerSuccesses>targetSuccesses)
    {
        std::cout << "[Combat] l'Attaquant gagne, la cible est envoyée à l'hopital"<<std::endl;
        target->set_place(Hospital);

    }
    else if (targetSuccesses>attackerSuccesses)
    {
        std::cout << "[Combat] la Cible gagne, l'attaquant est envoyé à l'hopital"<<std::endl;
        attacker->set_place(Hospital);
    }
    else
    {
        //Egalité : rien ne se passe
        std::cout << "[Combat] Egalité ! ("<<attackerSuccesses<<"-"<<targetSuccesses<<"). Rien ne se passe"<<std::endl;
    }
}
