#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/ClassicTile.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(ClassicTile_compilation_test)
{
    state::Position pos(1,1);
    state::ClassicTile classic_tile(pos);
    (void)classic_tile;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(ClassicTile_effect_test)
{
    state::Position pos(1,1);
    state::ClassicTile classic_tile(pos);
    BOOST_CHECK_NO_THROW(classic_tile.effect());
}

BOOST_AUTO_TEST_CASE(ClassicTile_unique_ptr_destructor_test)
{
    std::unique_ptr<state::ClassicTile> classic_tile=std::make_unique<state::ClassicTile>(state::Position(1,1));

    BOOST_CHECK(classic_tile);
    classic_tile.reset();
    BOOST_CHECK(!classic_tile);
}