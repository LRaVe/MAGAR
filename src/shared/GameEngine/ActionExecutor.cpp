#include "GameEngine/ActionExecutor.h"
#include "state/GameState.h"
#include "state/Action.h"  
#include "state/AttackAction.h"
#include "state/MoveAction.h"
#include "state/HealAction.h"
#include "state/ReviveAction.h"
#include "state/CastAction.h"



namespace GameEngine {

    ActionExecutor::ActionExecutor() = default;

    ActionExecutor::~ActionExecutor() = default;

    void ActionExecutor::execute(state::Action& action, state::GameState& state) {
        // Implementation of executing an action on the game state
        action.execute(state);
    }



}