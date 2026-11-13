#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/DrawDice.h"
#include <algorithm>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(DrawDice_initially_empty)
{
    state::DrawDice dice;
    BOOST_CHECK(dice.get_draw().empty());
}

BOOST_AUTO_TEST_CASE(DrawDice_rolls_requested_number)
{
    state::DrawDice dice;
    dice.roll(5);

    const auto draw = dice.get_draw();

    BOOST_REQUIRE_EQUAL(draw.size(), 5);

    for (const state::Dice value : draw) {
        BOOST_CHECK(
            value == state::Dice::WARRIOR ||
            value == state::Dice::SORCERER ||
            value == state::Dice::TRISKELL
        );
    }
}

BOOST_AUTO_TEST_CASE(DrawDice_roll_replaces_previous_draw)
{
    state::DrawDice dice;

    dice.roll(5);
    dice.roll(2);

    BOOST_CHECK_EQUAL(dice.get_draw().size(), 2);
}

BOOST_AUTO_TEST_CASE(DrawDice_zero_roll_is_empty)
{
    state::DrawDice dice;
    dice.roll(0);

    BOOST_CHECK(dice.get_draw().empty());
}