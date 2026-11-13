#include <boost/test/unit_test.hpp>
#include <memory>

#include <State/Board.h>
#include <State/CenterTile.h>
#include <State/ClassicTile.h>
#include <State/StarTile.h>

BOOST_AUTO_TEST_CASE(Board_compilation_test)
{
    State::Board board;
    (void)board;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Board_initializes_center_tile)
{
    State::Board board;

    std::shared_ptr<State::Tile> tile =
        board.get_tile_from(State::Position(0, 0));

    BOOST_REQUIRE(tile);
    BOOST_CHECK(dynamic_cast<State::CenterTile*>(tile.get()));
    BOOST_CHECK_EQUAL(tile->getPosition().q, 0);
    BOOST_CHECK_EQUAL(tile->getPosition().r, 0);
}

BOOST_AUTO_TEST_CASE(Board_stores_and_retrieves_tile)
{
    State::Board board;
    const State::Position position(1, -1);

    board.set_tile_at(
        position,
        std::make_shared<State::ClassicTile>(position));

    std::shared_ptr<State::Tile> tile = board.get_tile_from(position);

    BOOST_REQUIRE(tile);
    BOOST_CHECK(dynamic_cast<State::ClassicTile*>(tile.get()));
    BOOST_CHECK_EQUAL(tile->getPosition().q, 1);
    BOOST_CHECK_EQUAL(tile->getPosition().r, -1);
}

BOOST_AUTO_TEST_CASE(Board_retrieving_tile_removes_it)
{
    State::Board board;
    const State::Position position(1, -1);

    board.set_tile_at(
        position,
        std::make_shared<State::ClassicTile>(position));

    std::shared_ptr<State::Tile> first = board.get_tile_from(position);
    std::shared_ptr<State::Tile> second = board.get_tile_from(position);

    BOOST_REQUIRE(first);
    BOOST_CHECK(!second);
}