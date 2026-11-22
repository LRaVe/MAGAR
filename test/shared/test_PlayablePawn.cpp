#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/Sorcerer.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_compilation_test)
{
    {
        // check that the code compiles
        state::PlayablePawn playable_pawn(state::Color::Red, state::Position(0,0));
        (void)playable_pawn; // avoid unused variable warning
        BOOST_CHECK(true); 
    }
}

BOOST_AUTO_TEST_CASE(PlayablePawn_initialization_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK_EQUAL(playable_pawn.get_position().q, 0);
    BOOST_CHECK_EQUAL(playable_pawn.get_position().r, 0);
    BOOST_CHECK_EQUAL(playable_pawn.get_position().s(), 0);
    BOOST_CHECK_EQUAL(playable_pawn.get_attack(),0);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Camp);
    BOOST_CHECK_EQUAL(playable_pawn.get_nb_moves(),0);
    BOOST_CHECK_EQUAL(playable_pawn.get_color(),state::Color::Red);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_set_attack)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK_EQUAL(playable_pawn.get_attack(),0);
    playable_pawn.set_attack(5);
    BOOST_CHECK_EQUAL(playable_pawn.get_attack(),5);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_set_place)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Camp);
    playable_pawn.set_place(state::Place::Hospital);
    BOOST_CHECK_EQUAL(playable_pawn.get_place(),state::Place::Hospital);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_as_playable_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    BOOST_CHECK(playable_pawn.as_playable()==&playable_pawn);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_class_dice_test)
{
    state::PlayablePawn playable_pawn(state::Color::Red,state::Position(0,0));
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    BOOST_CHECK(!playable_pawn.class_dice().has_value());
    BOOST_CHECK(warrior.class_dice()==state::Dice::WARRIOR);
    BOOST_CHECK(sorcerer.class_dice()==state::Dice::SORCERER);
}

BOOST_AUTO_TEST_CASE(PlayablePawn_unique_ptr_destructor_test)
{
    std::unique_ptr<state::PlayablePawn> playable_pawn=std::make_unique<state::PlayablePawn>(state::Color::Red,state::Position(0,0));
    BOOST_CHECK(playable_pawn);
    playable_pawn.reset();
    BOOST_CHECK(!playable_pawn);
}