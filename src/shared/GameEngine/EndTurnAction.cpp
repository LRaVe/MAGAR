#include "EndTurnAction.h"


namespace GameEngine {

    using namespace state;

    EndTurnAction::EndTurnAction() {
    }

    EndTurnAction::~EndTurnAction() = default;

    void EndTurnAction::execute(GameState& state) {

    }

    bool EndTurnAction::validate(GameEngine::RuleEngine& rules, GameState& state) {
        return true; // Always valid
    }   

}