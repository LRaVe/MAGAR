#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Pawn.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Pawn_compilation_test)
{
    {
        // check that the code compiles
        state::Pawn pawn(state::Position(0,0));
        (void)pawn; // avoid unused variable warning
        BOOST_CHECK(true); 
    }
}

BOOST_AUTO_TEST_CASE(Pawn_getters_test)
{
    {
        state::Pawn pawn(state::Position(1,2));
        BOOST_CHECK_EQUAL(pawn.get_position().q,1);
        BOOST_CHECK_EQUAL(pawn.get_position().r,2);
        BOOST_CHECK_EQUAL(pawn.get_position().s(),-3);

    }
}


BOOST_AUTO_TEST_CASE(Pawn_setters_test)
{
    {
        state::Pawn pawn(state::Position(1,2));
        pawn.set_position(state::Position(3,4));
        BOOST_CHECK_EQUAL(pawn.get_position().q,3);
        BOOST_CHECK_EQUAL(pawn.get_position().r,4);
        BOOST_CHECK_EQUAL(pawn.get_position().s(),-7);

    }
}


BOOST_AUTO_TEST_CASE(Pawn_distance_same_position)
{
    state::Pawn pawn1(state::Position(1,2));
    state::Pawn pawn2(state::Position(1,2));
    BOOST_CHECK_EQUAL(pawn1.get_distance_from(pawn2),0);
}
