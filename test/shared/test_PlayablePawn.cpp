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

BOOST_AUTO_TEST_CASE(PlayablePawn_initialization_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK_EQUAL(playable_pawn.get_position().q, 0);
    BOOST_CHECK_EQUAL(playable_pawn.get_position().r, 0);
    BOOST_CHECK_EQUAL(playable_pawn.get_position().s(), 0);
    BOOST_CHECK_EQUAL(playable_pawn.get_attack(),0);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Camp);
    BOOST_CHECK_EQUAL(playable_pawn.get_nb_moves(),0);
    BOOST_CHECK_EQUAL(playable_pawn.get_color(),state::Color::Red);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_set_attack)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK_EQUAL(playable_pawn.get_attack(),0);
    playable_pawn.set_attack(5);
    BOOST_CHECK_EQUAL(playable_pawn.get_attack(),5);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_set_place)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Camp);
    playable_pawn.set_place(state::Place::Hospital);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Hospital);
}