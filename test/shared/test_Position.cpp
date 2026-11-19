#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Position.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Position_compilation_test)
{
    state::Position pos(1,2);
    (void)pos;
    BOOST_CHECK_EQUAL(pos.q, 1);
    BOOST_CHECK_EQUAL(pos.r, 2);
}

BOOST_AUTO_TEST_CASE(Position_is_in_radius_test)
{
    state::Position pos(1,2);
    BOOST_CHECK(pos.is_in_radius(3));
    BOOST_CHECK(!pos.is_in_radius(2));
}

BOOST_AUTO_TEST_CASE(Position_is_adjacent_to_test)
{
    state::Position pos1(1,2);
    state::Position pos2(1,3);
    state::Position pos3(2,2);
    state::Position pos4(0,0);
    BOOST_CHECK(pos1.is_adjacent_to(pos2));
    BOOST_CHECK(pos1.is_adjacent_to(pos3));
    BOOST_CHECK(!pos1.is_adjacent_to(pos4));
    BOOST_CHECK(pos2.is_adjacent_to(pos3));
}

BOOST_AUTO_TEST_CASE(Position_neihbor_test)
{
    state::Position pos(1,2);
    state::Position neighbor_lim1=pos.neighbor(-1);
    state::Position neighbor_lim2=pos.neighbor(6);
    state::Position neighbor1=pos.neighbor(0);
    state::Position neighbor2=pos.neighbor(1);
    state::Position neighbor3=pos.neighbor(2);
    state::Position neighbor4=pos.neighbor(3);
    state::Position neighbor5=pos.neighbor(4);
    state::Position neighbor6=pos.neighbor(5);
    
    BOOST_CHECK_EQUAL(neighbor1.q,2);
    BOOST_CHECK_EQUAL(neighbor1.r,2);
    BOOST_CHECK_EQUAL(neighbor2.q,2);
    BOOST_CHECK_EQUAL(neighbor2.r,1);
    BOOST_CHECK_EQUAL(neighbor3.q,1);
    BOOST_CHECK_EQUAL(neighbor3.r,1);
    BOOST_CHECK_EQUAL(neighbor4.q,0);
    BOOST_CHECK_EQUAL(neighbor4.r,2);
    BOOST_CHECK_EQUAL(neighbor5.q,0);
    BOOST_CHECK_EQUAL(neighbor5.r,3);
    BOOST_CHECK_EQUAL(neighbor6.q,1);
    BOOST_CHECK_EQUAL(neighbor6.r,3);
    BOOST_CHECK_EQUAL(neighbor_lim1.q,1);
    BOOST_CHECK_EQUAL(neighbor_lim1.r,2);
    BOOST_CHECK_EQUAL(neighbor_lim2.q,1);
    BOOST_CHECK_EQUAL(neighbor_lim2.r,2);
}

BOOST_AUTO_TEST_CASE(Position_neighbors_list_test)
{
    state::Position pos(1,2);
    auto result=pos.neighbors();
    BOOST_CHECK_EQUAL(result.size(), 6);
    BOOST_CHECK_EQUAL(result[0].q,2);
    BOOST_CHECK_EQUAL(result[0].r,2);
    BOOST_CHECK_EQUAL(result[1].q,2);
    BOOST_CHECK_EQUAL(result[1].r,1);
    BOOST_CHECK_EQUAL(result[2].q,1);
    BOOST_CHECK_EQUAL(result[2].r,1);
    BOOST_CHECK_EQUAL(result[3].q,0);
    BOOST_CHECK_EQUAL(result[3].r,2);
    BOOST_CHECK_EQUAL(result[4].q,0);
    BOOST_CHECK_EQUAL(result[4].r,3);
    BOOST_CHECK_EQUAL(result[5].q,1);
    BOOST_CHECK_EQUAL(result[5].r,3);
}

BOOST_AUTO_TEST_CASE(Position_ring_test)
{
    state::Position pos(1,2);
    auto result=pos.ring(1);
    auto result2=pos.ring(0);
    auto result3=pos.ring(-1);
    auto result4=pos.ring(2);

    BOOST_CHECK_EQUAL(result.size(), 6);
    BOOST_CHECK_EQUAL(result2.size(),1);
    BOOST_CHECK_EQUAL(result3.size(),0);
    BOOST_CHECK_EQUAL(result4.size(),12);

    BOOST_CHECK_EQUAL(result2[0].q,1);
    BOOST_CHECK_EQUAL(result2[0].r,2);
    
    const std::vector<state::Position> expected = {
        state::Position(0, 3),
        state::Position(1, 3),
        state::Position(2, 2),
        state::Position(2, 1),
        state::Position(1, 1),
        state::Position(0, 2)
    };

    for (std::size_t i = 0; i < expected.size(); ++i) {
        BOOST_CHECK_EQUAL(result[i].q, expected[i].q);
        BOOST_CHECK_EQUAL(result[i].r, expected[i].r);
    }

    for (const state::Position& position : result4) {
        BOOST_CHECK_EQUAL(pos.distance_to(position), 2);
    }

}