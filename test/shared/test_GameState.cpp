#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/GameState.h"


BOOST_AUTO_TEST_CASE(GameState_initial_state)
{
    state::GameState game_state;

    BOOST_CHECK_EQUAL(game_state.get_turn(), 0);
    BOOST_CHECK_EQUAL(game_state.get_players().size(), 4);
    BOOST_CHECK(game_state.get_possible_actions().empty());
}

BOOST_AUTO_TEST_CASE(GameState_initial_players)
{
    state::GameState game_state;
    auto players = game_state.get_players();

    BOOST_CHECK_EQUAL(players.size(), 4);
    for (auto& player : players) {
        BOOST_CHECK_EQUAL(
            player.get_warrior().get_place(),
            state::Place::Camp
        );
        BOOST_CHECK_EQUAL(
            player.get_sorcerer().get_place(),
            state::Place::Camp
        );
    }
}

BOOST_AUTO_TEST_CASE(GameState_current_player)
{
    state::GameState game_state;
    state::Player& current_player = game_state.get_current_player();

    BOOST_CHECK_EQUAL(
        current_player.get_warrior().get_place(),
        state::Place::Camp
    );
    BOOST_CHECK_EQUAL(
        current_player.get_sorcerer().get_place(),
        state::Place::Camp
    );
    BOOST_CHECK_EQUAL(
        &current_player,
        &game_state.get_current_player()
    );
}

BOOST_AUTO_TEST_CASE(GameState_add_player)
{
    state::GameState game_state;
    const std::size_t initial_size = game_state.get_players().size();

    game_state.add_player(
        state::Color::Red,
        state::Position(10, 10),
        state::Position(10, 11)
    );

    auto players = game_state.get_players();
    BOOST_REQUIRE_EQUAL(players.size(), initial_size + 1);
    BOOST_CHECK_EQUAL(
        players.back().get_warrior().get_place(),
        state::Place::Camp
    );
    BOOST_CHECK_EQUAL(
        players.back().get_sorcerer().get_place(),
        state::Place::Camp
    );
}

BOOST_AUTO_TEST_CASE(GameState_board)
{
    state::GameState game_state;
    state::Board& board = game_state.get_board();

    BOOST_CHECK_EQUAL(&board, &game_state.get_board());
}

BOOST_AUTO_TEST_CASE(GameState_initial_possible_actions)
{
    state::GameState game_state;
    auto actions = game_state.get_possible_actions();
    actions.clear();

    BOOST_CHECK(game_state.get_possible_actions().empty());
}

BOOST_AUTO_TEST_CASE(GameState_initial_pawn_positions)
{
    state::GameState game_state;

    const auto stone_position = game_state.get_stone().get_position();
    const auto dragon_position = game_state.get_dragon().get_position();

    BOOST_CHECK_EQUAL(stone_position.q, 0);
    BOOST_CHECK_EQUAL(stone_position.r, 0);
    BOOST_CHECK_EQUAL(dragon_position.q, 0);
    BOOST_CHECK_EQUAL(dragon_position.r, 0);
}

BOOST_AUTO_TEST_CASE(GameState_destruction)
{
    BOOST_CHECK_NO_THROW({
        state::GameState game_state;
        game_state.add_player(
            state::Color::Red,
            state::Position(10, 10),
            state::Position(10, 11)
        );
    });
}
