//
// Created by plt on 11/12/26.
//

#include "GameEngine/HealAction.h"
#include "state/PlayablePawn.h"
#include "state/GameState.h"
#include "state/Dice.h"
#include "state/Place.h"
#include "GameEngine/RuleEngine.h"
#include <algorithm>

namespace GameEngine
{
    using namespace state;

    HealAction::HealAction(PlayablePawn* target, const std::vector<state::Dice>& draw)
        : target(target), draw(draw) {
    }

    HealAction::~HealAction() = default;


    bool HealAction::is_target_in_hospital() const {
        return (target != nullptr && target->get_place() == Place::Hospital);
    }


    bool HealAction::has_valid_dice_combination() const {

        if (!target) return false;

        const auto kind = target->class_dice();
        if (!kind) return false;

        const auto triskell_count = std::count(draw.begin(), draw.end(), TRISKELL);
        const auto own_count 	  = std::count(draw.begin(), draw.end(), *kind);

        return (own_count == 1 && triskell_count == 2) ||
               (own_count == 2 && triskell_count == 1);
    }


    bool HealAction::can_apply() const {
        return is_target_in_hospital() && has_valid_dice_combination();
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