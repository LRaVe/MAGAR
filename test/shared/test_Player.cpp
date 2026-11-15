#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Player.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Player_compilation_test)
{
    state::Player player(state::Color::Red,state::Position(0,0),state::Position(1,1));
    (void)player;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Player_getColor_test)
{
    state::Player player(state::Color::Red,state::Position(0,0),state::Position(1,1));
    BOOST_CHECK_EQUAL(player.getColor(),state::Color::Red);
}

BOOST_AUTO_TEST_CASE(Player_get_warrior_test)
{
    state::Player player(state::Color::Red,state::Position(0,0),state::Position(1,1));
    BOOST_CHECK_EQUAL(player.get_warrior().get_position().q,0);
    BOOST_CHECK_EQUAL(player.get_warrior().get_position().r,0);
    BOOST_CHECK_EQUAL(player.get_warrior().get_position().s(),0);
}

BOOST_AUTO_TEST_CASE(Player_get_sorcerer_test)
{
    state::Player player(state::Color::Red,state::Position(0,0),state::Position(1,1));
    BOOST_CHECK_EQUAL(player.get_sorcerer().get_position().q,1);
    BOOST_CHECK_EQUAL(player.get_sorcerer().get_position().r,1);
    BOOST_CHECK_EQUAL(player.get_sorcerer().get_position().s(),-2);
}
