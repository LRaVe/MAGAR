#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/Telekinesis.h"
#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/Stone.h"
#include "../../src/shared/state/GameState.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Telekinesis_compilation_test)
{
    state::Position destination(0,0);
    GameEngine::Telekinesis telekinesis(destination);
    (void)telekinesis;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Telekinesis_get_nb_of_dice_warrior_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(0,0));
    state::GameState state;

    state.get_stone().set_position(state::Position(0,0));

    BOOST_CHECK_EQUAL(telekinesis.get_nb_of_dice(state), 3);
}

BOOST_AUTO_TEST_CASE(Telekinesis_get_nb_of_dice_sorcerer_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(0,0));
    state::GameState state;

    state.get_stone().set_position(state::Position(0,1));

    BOOST_CHECK_EQUAL(telekinesis.get_nb_of_dice(state), 3);
}

BOOST_AUTO_TEST_CASE(Telekinesis_get_nb_of_dice_later_player_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(0,0));
    state::GameState state;

    state.get_stone().set_position(state::Position(1,0));

    BOOST_CHECK_EQUAL(telekinesis.get_nb_of_dice(state), 3);
}

BOOST_AUTO_TEST_CASE(Telekinesis_get_nb_of_dice_no_pawn_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(0,0));
    state::GameState state;

    state.get_stone().set_position(state::Position(5,5));

    BOOST_CHECK_EQUAL(telekinesis.get_nb_of_dice(state), 1);
}

BOOST_AUTO_TEST_CASE(Telekinesis_list_moves_center_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(0,0));
    state::GameState state;
    
    state.get_stone().set_position(state::Position(0,0));
    const auto moves=telekinesis.ListOfMoves(state);
    BOOST_CHECK_EQUAL(moves.size(),6);
}

BOOST_AUTO_TEST_CASE(Telekinesis_list_moves_edge_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(0,0));
    state::GameState state;

    state.get_stone().set_position(state::Position(5,-5));
    const auto moves=telekinesis.ListOfMoves(state);
    BOOST_CHECK_EQUAL(moves.size(),3);
}

BOOST_AUTO_TEST_CASE(Telekinesis_execute_test)
{
    GameEngine::Telekinesis telekinesis(state::Position(4,-2));
    state::GameState state;
    telekinesis.execute(state);
    BOOST_CHECK_EQUAL(state.get_stone().get_position().q, 4);
    BOOST_CHECK_EQUAL(state.get_stone().get_position().r, -2);
}