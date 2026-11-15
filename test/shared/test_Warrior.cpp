#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/GameState.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Warrior_compilation_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    (void)warrior;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Warrior_attack_pawn_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    state::GameState state;
    state::PlayablePawn pawn(state::Color::Blue,state::Position(1,0));
    warrior.attack_pawn(&pawn,state);
    BOOST_CHECK_EQUAL(pawn.get_position().q,1);
    BOOST_CHECK_EQUAL(pawn.get_position().r,0);
}