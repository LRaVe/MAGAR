//
// Created by plt on 11/12/26.
//

#include "state/HealAction.h"
#include "state/PlayablePawn.h"
#include "state/Warrior.h"
#include "state/Sorcerer.h"
#include <algorithm>

namespace state
{
    HealAction::HealAction(PlayablePawn* target, const std::vector<state::Dice>& draw)
        : target(target), draw(draw) {
    }

    HealAction::~HealAction() = default;

    bool HealAction::can_apply() const
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
            return (warrior_count == 1 && triskell_count == 2) || (warrior_count == 2 && triskell_count == 1);
        }
        if (dynamic_cast<const Sorcerer*>(target) != nullptr) {
            return (sorcerer_count == 1 && triskell_count == 2) || (sorcerer_count == 2 && triskell_count == 1);
        }

        return false;
    }

    void HealAction::execute(GameState& state)
    {
        if (can_apply() && target != nullptr)
        {
            target->set_place(Arena);
        }
    }
}