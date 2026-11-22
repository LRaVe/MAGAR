#include <boost/test/unit_test.hpp>
#include <memory>
#include "../../src/shared/state/CenterTile.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(CenterTile_compilation_test)
{
    state::Position pos(0,0);
    state::CenterTile center_tile(pos);
    (void)center_tile;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(CenterTile_effect_test)
{
    state::Position pos(0,0);
    state::CenterTile center_tile(pos);
    BOOST_CHECK_NO_THROW(center_tile.effect());
}

BOOST_AUTO_TEST_CASE(CenterTile_unique_ptr_destructor_test)
{
    std::unique_ptr<state::CenterTile> center_tile=std::make_unique<state::CenterTile>(state::Position(0,0));

    BOOST_CHECK(center_tile);
    center_tile.reset();
    BOOST_CHECK(!center_tile);
}