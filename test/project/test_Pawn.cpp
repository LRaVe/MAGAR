#include <boost/test/unit_test.hpp>
#include <State/Pawn.h>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Pawn_compilation_test)
{
    {
        // check that the code compiles
        State::Pawn pawn(State::Position(0,0));
        (void)pawn; // avoid unused variable warning
        BOOST_CHECK(true); 
    }
}

/* BOOST_AUTO_TEST_CASE(Pawn_getters_test)
{
    {
        State::Pawn pawn(State::Position(1,2));
        BOOST_CHECK_EQUAL(pawn.get_position().q,1);
        BOOST_CHECK_EQUAL(pawn.get_position().r,2);
        BOOST_CHECK_EQUAL(pawn.get_position().s(),0);

    }
}
    */

/*
BOOST_AUTO_TEST_CASE(Pawn_setters_test)
{
    {
        State::Pawn pawn(State::Position(1,2));
        pawn.set_position(State::Position(3,4));
        BOOST_CHECK_EQUAL(pawn.get_position().q,3);
        BOOST_CHECK_EQUAL(pawn.get_position().r,4);
        BOOST_CHECK_EQUAL(pawn.get_position().s(),0);

    }
}
 */