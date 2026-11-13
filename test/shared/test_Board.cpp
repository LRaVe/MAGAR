#include <boost/test/unit_test.hpp>
#include <memory>

#include "../../src/shared/state/Board.h"
#include "../../src/shared/state/CenterTile.h"
#include "../../src/shared/state/ClassicTile.h"
#include "../../src/shared/state/StarTile.h"

BOOST_AUTO_TEST_CASE(Board_compilation_test)
{
    state::Board board;
    (void)board;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Board_initializes_center_tile)
{
    state::Board board;

    std::shared_ptr<state::Tile> tile =
        board.get_tile_from(state::Position(0, 0));

    BOOST_REQUIRE(tile);
    BOOST_CHECK(dynamic_cast<state::CenterTile*>(tile.get()));
    BOOST_CHECK_EQUAL(tile->getPosition().q, 0);
    BOOST_CHECK_EQUAL(tile->getPosition().r, 0);
}

BOOST_AUTO_TEST_CASE(Board_stores_and_retrieves_tile)
{
    state::Board board;
    const state::Position position(1, -1);

    board.set_tile_at(
        position,
        std::make_shared<state::ClassicTile>(position));

    std::shared_ptr<state::Tile> tile = board.get_tile_from(position);

    BOOST_REQUIRE(tile);
    BOOST_CHECK(dynamic_cast<state::ClassicTile*>(tile.get()));
    BOOST_CHECK_EQUAL(tile->getPosition().q, 1);
    BOOST_CHECK_EQUAL(tile->getPosition().r, -1);
}

BOOST_AUTO_TEST_CASE(Board_retrieving_tile_removes_it)
{
    state::Board board;
    const state::Position position(1, -1);

    board.set_tile_at(
        position,
        std::make_shared<state::ClassicTile>(position));

    std::shared_ptr<state::Tile> first = board.get_tile_from(position);
    std::shared_ptr<state::Tile> second = board.get_tile_from(position);

    BOOST_REQUIRE(first);
    BOOST_CHECK(!second);
}