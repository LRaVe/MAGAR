#include <boost/test/unit_test.hpp>
#include <State/GameState.h>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(GameState_compilation_test)
{
    {
        // check that the code compiles
        State::GameState game_state;
        (void)game_state; // avoid unused variable warning
        BOOST_CHECK(true); 
    }
}

BOOST_AUTO_TEST_CASE(GameState_getters_test)
{
    {
        State::GameState game_state;
        BOOST_CHECK_EQUAL(game_state.get_turn(),0);
        BOOST_CHECK_EQUAL(game_state.get_players().size(),4);

    }
}