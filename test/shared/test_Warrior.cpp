#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/GameState.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Warrior_compilation_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    (void)warrior;
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(Warrior_class_dice_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    BOOST_CHECK(warrior.class_dice().has_value());
    BOOST_CHECK(warrior.class_dice()==state::Dice::WARRIOR);
}

BOOST_AUTO_TEST_CASE(Warrior_unique_ptr_destructor_test)
{
    std::unique_ptr<state::Warrior> warrior=std::make_unique<state::Warrior>(state::Color::Red,state::Position(0,0));

    BOOST_CHECK(warrior);
    warrior.reset();
    BOOST_CHECK(!warrior);
}