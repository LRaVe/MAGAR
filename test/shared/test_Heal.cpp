#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Heal.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/GameState.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Heal_compilation_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    state::Heal heal(&playable_pawn);
    (void)heal;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Heal_get_nb_of_dice_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    state::Heal heal(&playable_pawn);
    state::GameState state;
    int nb_of_dice=heal.get_nb_of_dice(state);
    BOOST_CHECK_EQUAL(nb_of_dice,2);
}

BOOST_AUTO_TEST_CASE(Heal_execute_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    playable_pawn.set_place(state::Place::Hospital);
    state::Heal heal(&playable_pawn);
    state::GameState state;
    heal.execute(state);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Camp);
    playable_pawn.set_place(state::Place::Arena);
    heal.execute(state);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Arena);
}

BOOST_AUTO_TEST_CASE(Heal_execute_with_null_target_test)
{
    state::Heal heal(nullptr);
    state::GameState state;

    BOOST_CHECK_NO_THROW(heal.execute(state));
}