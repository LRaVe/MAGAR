#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "../../src/shared/state/Board.h"
#include "../../src/shared/state/CenterTile.h"
#include "../../src/shared/state/ClassicTile.h"
#include "../../src/shared/state/StarTile.h"
#include "../../src/shared/state/Position.h"

std::vector<state::Position> get_circle_tile_list(int radius, int center);

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
    BOOST_CHECK_EQUAL(tile->get_position().q, 0);
    BOOST_CHECK_EQUAL(tile->get_position().r, 0);
}


BOOST_AUTO_TEST_CASE(Board_get_circle_tile_list_applies_offset)
{
    const std::vector<state::Position> positions =
        get_circle_tile_list(1, 2);

    BOOST_REQUIRE_EQUAL(positions.size(), 7);

    const bool contains_center =
        std::any_of(positions.begin(), positions.end(),
            [](const state::Position& position) {
                return position.q == 2 && position.r == 2;
            });

    BOOST_CHECK(contains_center);

    for (const state::Position& position : positions) {
        const int distance = std::max({
            std::abs(position.q - 2),
            std::abs(position.r - 2),
            std::abs((position.q - 2) + (position.r - 2))
        });
        BOOST_CHECK_LE(distance, 1);
    }
}

BOOST_AUTO_TEST_CASE(Board_get_tiles_returns_only_present_tiles)
{
    const state::Board board;
    const std::vector<std::shared_ptr<state::Tile>> tiles =
        board.get_tiles();

    BOOST_REQUIRE(!tiles.empty());

    for (const std::shared_ptr<state::Tile>& tile : tiles) {
        BOOST_REQUIRE(tile);
        BOOST_CHECK(tile->get_position().q >= -5);
        BOOST_CHECK(tile->get_position().q <= 5);
        BOOST_CHECK(tile->get_position().r >= -5);
        BOOST_CHECK(tile->get_position().r <= 5);
    }
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
    BOOST_CHECK_EQUAL(tile->get_position().q, 1);
    BOOST_CHECK_EQUAL(tile->get_position().r, -1);
}
