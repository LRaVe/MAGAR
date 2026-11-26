#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/Engine.h"

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


