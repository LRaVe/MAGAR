#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/PlayablePawn.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_compilation_test)
{
    {
        // check that the code compiles
        state::PlayablePawn playable_pawn(state::Color::Red, state::Position(0,0));
        (void)playable_pawn; // avoid unused variable warning
        BOOST_CHECK(true); 
    }
}