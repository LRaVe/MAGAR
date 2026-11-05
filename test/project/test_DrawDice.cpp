#include <boost/test/unit_test.hpp>
#include <State/DrawDice.h>
#include <algorithm>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(DrawDice_initially_empty)
{
    State::DrawDice dice;
    BOOST_CHECK(dice.get_draw().empty());
}

BOOST_AUTO_TEST_CASE(DrawDice_rolls_requested_number)
{
    State::DrawDice dice;
    dice.roll(5);

    const auto draw = dice.get_draw();

    BOOST_REQUIRE_EQUAL(draw.size(), 5);

    for (const State::Dice value : draw) {
        BOOST_CHECK(
            value == State::Dice::WARRIOR ||
            value == State::Dice::SORCERER ||
            value == State::Dice::TRISKELL
        );
    }
}

BOOST_AUTO_TEST_CASE(DrawDice_roll_replaces_previous_draw)
{
    State::DrawDice dice;

    dice.roll(5);
    dice.roll(2);

    BOOST_CHECK_EQUAL(dice.get_draw().size(), 2);
}

BOOST_AUTO_TEST_CASE(DrawDice_zero_roll_is_empty)
{
    State::DrawDice dice;
    dice.roll(0);

    BOOST_CHECK(dice.get_draw().empty());
}