#include <boost/test/unit_test.hpp>
#include <memory>
#include "../../src/shared/state/NestTile.h"

BOOST_AUTO_TEST_CASE(NestTile_compilation_test)
{
    state::Position pos(1,0);
    state::NestTile nest_tile(pos);
    (void)nest_tile;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(NestTile_effect_test)
{
    state::Position pos(1,0);
    state::NestTile nest_tile(pos);
    BOOST_CHECK_NO_THROW(nest_tile.effect());
}

BOOST_AUTO_TEST_CASE(NestTile_is_nested_tile_test)
{
    state::NestTile nest_tile(state::Position(1,0));
    BOOST_CHECK(nest_tile.is_nested_tile());
}

BOOST_AUTO_TEST_CASE(NestTile_unique_ptr_destructor_test)
{
    std::unique_ptr<state::NestTile> nest_tile=std::make_unique<state::NestTile>(state::Position(1,0));

    BOOST_CHECK(nest_tile);
    nest_tile.reset();
    BOOST_CHECK(!nest_tile);
}