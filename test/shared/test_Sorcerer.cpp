#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Sorcerer.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/state/Spell.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(Sorcerer_compilation_test)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    (void)sorcerer;
    BOOST_CHECK(true);
}

class TestSpell : public state::Spell {
public :
    mutable int execution_count=0;
    void execute(state::GameState& state) const override {
        execution_count=execution_count+1;
    }
};

BOOST_AUTO_TEST_CASE(Sorcerer_can_cast_only_once_per_turn)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    state::GameState state;
    TestSpell spell;

    BOOST_CHECK(sorcerer.cast_spell(spell,state));
    BOOST_CHECK(!sorcerer.cast_spell(spell,state));
    BOOST_CHECK_EQUAL(spell.execution_count,1);
}

BOOST_AUTO_TEST_CASE(Sorcerer_cast_after_reset) {
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    state::GameState state;
    TestSpell spell;

    BOOST_CHECK(sorcerer.cast_spell(spell,state));
    sorcerer.reset_spell_usage();
    BOOST_CHECK(sorcerer.cast_spell(spell,state));
    BOOST_CHECK_EQUAL(spell.execution_count,2);
}

BOOST_AUTO_TEST_CASE(Sorcerer_attack_pawn) {
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    state::GameState state;
    state::PlayablePawn pawn(state::Color::Blue,state::Position(1,0));
    sorcerer.attack_pawn(&pawn,state);
    BOOST_CHECK_EQUAL(pawn.get_position().q,1);
    BOOST_CHECK_EQUAL(pawn.get_position().r,0);
}