#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/GameEngine.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TurnManager_compilation_test)
{
    GameEngine::TurnManager turn_manager;
    (void)turn_manager;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(TurnManager_next_turn_test)
{
    state::GameState state;
    GameEngine::TurnManager turn_manager;
    BOOST_CHECK_NO_THROW(turn_manager.next_turn(state));
}
