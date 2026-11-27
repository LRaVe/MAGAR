#include "EndTurnAction.h"

#include "state/GameState.h"


namespace GameEngine {

    using namespace state;

    EndTurnAction::EndTurnAction() = default;

    EndTurnAction::~EndTurnAction() = default;

    void EndTurnAction::execute(GameState& state) {
    }

    bool EndTurnAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
        return true; // Always valid
    }   

}
