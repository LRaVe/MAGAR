//
// Created by plt on 11/12/26.
//

#include "GameEngine/HealAction.h"
#include "state/PlayablePawn.h"
#include "state/GameState.h"
#include "GameEngine/Heal.h"
#include "GameEngine/RuleEngine.h"
#include <algorithm>

namespace GameEngine
{
    using namespace state;

    HealAction::HealAction(PlayablePawn* target, const std::vector<state::Dice>& draw)
        : target(target), draw(draw) {
    }

    HealAction::~HealAction() = default;

    bool HealAction::can_apply() const {
        if (!target || target->get_place() != Place::Hospital) {
            return false;
        }

        const auto kind = target->class_dice();
        if (!kind) {
            return false;
        }

        const auto triskell_count = std::count(draw.begin(), draw.end(), TRISKELL);
        const auto own_count      = std::count(draw.begin(), draw.end(), *kind);

        return (own_count == 1 && triskell_count == 2) || (own_count == 2 && triskell_count == 1);
    }

    void HealAction::execute(GameState& state)
    {
        if (can_apply())
        {
            target->set_place(Camp);
        }
    }

    bool HealAction::validate(GameEngine::RuleEngine& rules, GameState& state){
        return false; // à implémenter plus tard, pour l'instant on ne valide pas les actions
    }
}