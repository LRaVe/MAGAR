#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/MoveAction.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/Sorcerer.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(MoveAction_compilation_test)
{
    state::PlayablePawn pawn(state::Color::Red,state::Position(0,0));
    state::Position destination(1,0);
    GameEngine::MoveAction action(&pawn,destination);
    (void)action;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(MoveAction_can_apply_null_target_test)
{
    state::Position destination(1,0);
    GameEngine::MoveAction action(nullptr,destination);
    state::GameState state;
    BOOST_CHECK(!action.can_apply(state));
}

BOOST_AUTO_TEST_CASE(MoveAction_can_apply_not_in_arena_test)
{
    
}
