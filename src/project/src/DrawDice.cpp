#include "State/DrawDice.h"
#include <random>

namespace State {

    DrawDice::DrawDice() { //constructeur
    }
    void DrawDice::roll(int nb_of_dice) { //méthode de lancer de dé, qui prends en entrée le nombre de dés lancer et retourne
        draw.clear(); //reset du précédent

        //definition des faces du dé
        static const Dice faces[6] = {
            WARRIOR, WARRIOR,
            SORCERER, SORCERER,
            TRISKELL, TRISKELL
          };

        //gestion de l'aléatoire
        static std::random_device rd;
        static std::mt19937 generator(rd()); //algo aléatoire
        std::uniform_int_distribution<int> distribution(0, 5); // Index de 0 à 5

        //gestion tirage
        for (int i = 0; i < nb_of_dice; ++i) {
            int random_index = distribution(generator);
            draw.push_back(faces[random_index]);
        }
    }

    std::vector<Dice> DrawDice::get_draw() const { //getter
        return draw;
    }

}