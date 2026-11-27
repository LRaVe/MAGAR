#include <boost/test/unit_test.hpp>
#include <memory>
#include "../../src/shared/state/Tile.h"

BOOST_AUTO_TEST_CASE(Tile_compilation_test)
{
    state::Position pos(0,0);
    state::Tile tile(pos);
    (void)tile;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Tile_effect_test)
{
    state::Position pos(0,0);
    state::Tile tile(pos);
    BOOST_CHECK_NO_THROW(tile.effect());
}

BOOST_AUTO_TEST_CASE(Tile_is_star_tile_test)
{
    state::Position pos(0,0);
    state::Tile tile(pos);
    BOOST_CHECK(!tile.is_star_tile());
}

BOOST_AUTO_TEST_CASE(Tile_is_nested_tile_test)
{
    state::Tile tile(state::Position(0,0));
    BOOST_CHECK(!tile.is_nested_tile());
}

BOOST_AUTO_TEST_CASE(Tile_get_position_test)
{
    state::Position pos(0,0);
    state::Tile tile(pos);
    BOOST_CHECK_EQUAL(tile.get_position().q,pos.q);
    BOOST_CHECK_EQUAL(tile.get_position().r,pos.r);
}

BOOST_AUTO_TEST_CASE(Tile_unique_ptr_destructor_test)
{
    std::unique_ptr<state::Tile> tile=std::make_unique<state::Tile>(state::Position(0,0));

    BOOST_CHECK(tile);
    tile.reset();
    BOOST_CHECK(!tile);
}