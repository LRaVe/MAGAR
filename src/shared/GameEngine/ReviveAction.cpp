//
// Created by plt on 11/12/26.
//

#include "GameEngine/ReviveAction.h"
#include "state/PlayablePawn.h"
#include "state/GameState.h"
#include "GameEngine/RuleEngine.h"
#include <algorithm>

namespace GameEngine
{
    using namespace state;

    ReviveAction::ReviveAction(PlayablePawn* target, const std::vector<state::Dice>& draw)
        : target(target), draw(draw) {
    }

    ReviveAction::~ReviveAction() = default;

    bool ReviveAction::is_target_in_cemetery() const
    {
        return (target != nullptr && target->get_place() == Place::Cimetery);
    }

    bool ReviveAction::has_valid_dice_combination() const
    {
        if (!target) return false;

        const auto kind = target->class_dice();
        if (!kind) return false;

        return std::count(draw.begin(), draw.end(), *kind) == 3;
    }


    bool ReviveAction::can_apply() const
    {
        return is_target_in_cemetery() && has_valid_dice_combination();
    }

    void ReviveAction::execute(GameState& state)
    {
        if (can_apply())
        {
            target->set_place(Camp); // Le pion ressuscité retourne au Camp
        }
    }

    bool ReviveAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
        return false; // à implémenter plus tard
    }
}