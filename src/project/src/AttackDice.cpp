#include "../include/State/AttackDice.h"
#include <random>

namespace State {

    AttackDice::AttackDice() { //constructeur
    }
    void AttackDice::roll(int nb_of_dice) { //méthode de lancer de dé, qui prends en entrée le nombre de dés lancer et retourne
        attack_draw.clear(); //reset du précédent

        //definition des faces du dé
        static const bool faces[6] = {
            true, true,
            true, true,
            false, false
          };

        //gestion de l'aléatoire
        static std::random_device rd;
        static std::mt19937 generator(rd()); //algo aléatoire
        std::uniform_int_distribution<int> distribution(0, 5); // Index de 0 à 5

        //gestion tirage
        for (int i = 0; i < nb_of_dice; ++i) {
            int random_index = distribution(generator);
            attack_draw.push_back(faces[random_index]);
        }
    }

    std::vector<bool> AttackDice::get_draw() const { //getter
        return attack_draw;
    }

}