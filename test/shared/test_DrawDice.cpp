#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/DrawDice.h"
#include <algorithm>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

/*
BOOST_AUTO_TEST_CASE(DrawDice_initially_empty)
{
    state::DrawDice dice;
    BOOST_CHECK(dice.get_draw().empty());
}
*/

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

BOOST_AUTO_TEST_CASE(DrawDice_has_dice_test)
{
    state::DrawDice dice;
    dice.roll(5);
    const auto draw=dice.get_draw();
    BOOST_CHECK(!draw.empty());
    for (const state::Dice value : draw) {
        BOOST_CHECK(dice.has_dice(value));
    }
}

BOOST_AUTO_TEST_CASE(DrawDice_consume_dice_test)
{
    state::DrawDice dice;
    dice.roll(5);

    std::vector<state::Dice> draw = dice.get_draw();
    BOOST_REQUIRE(!draw.empty());

    for (const state::Dice value : draw) {
        BOOST_REQUIRE(dice.has_dice(value));

        const std::vector<state::Dice> before = dice.get_draw();
        const std::size_t count_before =
            std::count(before.begin(), before.end(), value);

        BOOST_CHECK(dice.consume_dice(value));

        const std::vector<state::Dice> after = dice.get_draw();
        const std::size_t count_after =
            std::count(after.begin(), after.end(), value);

        BOOST_CHECK_EQUAL(count_after + 1, count_before);
    }
}

BOOST_AUTO_TEST_CASE(DrawDice_consume_missing_dice_test)
{
    state::DrawDice dice;
    dice.roll(3);

    state::Dice missing_face = state::Dice::WARRIOR;

    while (dice.has_dice(missing_face)) {
        BOOST_REQUIRE(dice.consume_dice(missing_face));
    }

    BOOST_CHECK(!dice.consume_dice(missing_face));
}