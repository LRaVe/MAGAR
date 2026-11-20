#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Resurrection.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/GameState.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Resurrection_compilation_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    state::Resurrection resurrection(&playable_pawn);
    (void)resurrection;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Resurrection_get_nb_of_dice_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    state::Resurrection resurrection(&playable_pawn);
    state::GameState state;
    int nb_of_dice=resurrection.get_nb_of_dice(state);
    BOOST_CHECK_EQUAL(nb_of_dice,4);
}

BOOST_AUTO_TEST_CASE(Resurrection_execute_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    playable_pawn.set_place(state::Place::Cimetery);
    state::Resurrection resurrection(&playable_pawn);
    state::GameState state;
    resurrection.execute(state);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Camp);
    playable_pawn.set_place(state::Place::Arena);
    resurrection.execute(state);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Arena);
}

BOOST_AUTO_TEST_CASE(Resurrection_execute_with_null_target_test)
{
    state::Resurrection resurrection(nullptr);
    state::GameState state;
    BOOST_CHECK_NO_THROW(resurrection.execute(state));
}