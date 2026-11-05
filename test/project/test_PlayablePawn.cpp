#include <boost/test/unit_test.hpp>
#include <State/PlayablePawn.h>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_compilation_test)
{
    {
        // check that the code compiles
        State::PlayablePawn playable_pawn(State::Color::Red, State::Position(0,0));
        (void)playable_pawn; // avoid unused variable warning
        BOOST_CHECK(true); 
    }
}