//
// Created by plt on 11/12/26.
//

#include "State/ReviveAction.h"
#include "State/PlayablePawn.h"
#include "State/Warrior.h"
#include "State/Sorcerer.h"
#include <algorithm>

namespace State
{
    ReviveAction::ReviveAction(PlayablePawn& target, const std::vector<State::Dice>& draw)
        : target(&target), draw(draw) {
    }

    ReviveAction::~ReviveAction() = default;

    bool ReviveAction::can_apply() const
    {
        // Sécurité au cas où target serait null
        if (!target) {
            return false;
        }

        // On vérifie que le pion est bien à l'hôpital
        if (target->get_place() != Place::Hospital) {
            return false;
        }

        // auto pour éviter le warning de clang tidy sur le retour (à la base int, peut être mis en long)
        auto triskell_count = std::count(draw.begin(), draw.end(), TRISKELL);
        auto warrior_count  = std::count(draw.begin(), draw.end(), WARRIOR);
        auto sorcerer_count = std::count(draw.begin(), draw.end(), SORCERER);

        if (dynamic_cast<const Warrior*>(target) != nullptr) {
            return warrior_count == 3;
        }
        if (dynamic_cast<const Sorcerer*>(target) != nullptr) {
            return sorcerer_count == 3;
        }

        return false;
    }

    void ReviveAction::execute(GameState& state)
    {
        if (can_apply() && target != nullptr)
        {
            target->set_place(Arena);
        }
    }
}