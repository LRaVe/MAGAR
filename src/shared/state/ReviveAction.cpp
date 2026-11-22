//
// Created by plt on 11/12/26.
//

#include "state/ReviveAction.h"
#include "state/PlayablePawn.h"
#include "state/GameState.h"
#include "GameEngine/RuleEngine.h"
#include <algorithm>

namespace state
{
    ReviveAction::ReviveAction(PlayablePawn* target, const std::vector<state::Dice>& draw)
        : target(target), draw(draw) {
    }

    ReviveAction::~ReviveAction() = default;

    bool ReviveAction::can_apply() const {
        if (!target || target->get_place() != Place::Cimetery) {
            return false;
        }

        const auto kind = target->class_dice();
        if (!kind) {
            return false;
        }

        return std::count(draw.begin(), draw.end(), *kind) == 3;
    }

    void ReviveAction::execute(GameState& state)
    {
        if (can_apply())
        {
            target->set_place(Camp);
        }
    }

    bool ReviveAction::validate(GameEngine::RuleEngine& rules, GameState& state){
        return false; // à implémenter plus tard, pour l'instant on ne valide pas les actions
    }
}