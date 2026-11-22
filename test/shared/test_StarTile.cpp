#include <boost/test/unit_test.hpp>
#include <memory>
#include "../../src/shared/state/StarTile.h"

BOOST_AUTO_TEST_CASE(StarTile_compilation_test)
{
    state::Position pos(0,0);
    state::StarTile star_tile(pos);
    (void)star_tile;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(StarTile_effect_test)
{
    state::Position pos(0,0);
    state::StarTile star_tile(pos);
    BOOST_CHECK_NO_THROW(star_tile.effect());
}

BOOST_AUTO_TEST_CASE(StarTile_is_star_tile_test)
{
    state::Position pos(0,0);
    state::StarTile star_tile(pos);
    BOOST_CHECK(star_tile.is_star_tile());
}

BOOST_AUTO_TEST_CASE(StarTile_unique_ptr_destructor_test)
{
    std::unique_ptr<state::StarTile> star_tile=std::make_unique<state::StarTile>(state::Position(0,0));

    BOOST_CHECK(star_tile);
    star_tile.reset();
    BOOST_CHECK(!star_tile);
}