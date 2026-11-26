#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/CastAction.h"
#include "../../src/shared/GameEngine/Spell.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/state/ClassicTile.h"
#include "../../src/shared/state/StarTile.h"
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

class TestSpell : public GameEngine::Spell {
public :
    mutable int execution_count=0;
    mutable bool executed=false;
    void execute(state::GameState& state) const override {
        (void)state;
        execution_count=execution_count+1;
        executed=true;
    }

    int get_nb_of_dice(state::GameState&) override {
        return 1;
    }
};

BOOST_AUTO_TEST_CASE(CastAction_compilation_test)
{
    state::PlayablePawn sorcerer(state::Color::Red,state::Position(0,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer,&spell);
    (void)cast_action;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(CastAction_isOnStarTile_test)
{
    GameEngine::CastAction cast_action_null(nullptr,nullptr);
    state::PlayablePawn sorcerer(state::Color::Red,state::Position(0,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer,&spell);
    state::GameState state;
    BOOST_CHECK(!cast_action_null.isOnStarTile(state));
    BOOST_CHECK(!cast_action.isOnStarTile(state));

    sorcerer.set_position(state::Position(1,-1));
    BOOST_CHECK(!cast_action.isOnStarTile(state));

    sorcerer.set_position(state::Position(2,-4));
    BOOST_CHECK(cast_action.isOnStarTile(state));
}

BOOST_AUTO_TEST_CASE(CastAction_isOnStarTile_tile_type_test)
{
    state::GameState state;
    state::PlayablePawn sorcerer(state::Color::Red, state::Position(3,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer, &spell);

    BOOST_CHECK(!cast_action.isOnStarTile(state));

    // check case where current_tile is not valid (nullptr)
    state.get_board().set_tile_at(
        state::Position(3,0),
        nullptr);
    sorcerer.set_position(state::Position(3,0));
    BOOST_CHECK(!cast_action.isOnStarTile(state));
}

BOOST_AUTO_TEST_CASE(CastAction_countSuccesses_test)
{
    state::PlayablePawn sorcerer(state::Color::Red,state::Position(0,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer,&spell);
    std::vector<bool> draw1={true,false,true,true};
    std::vector<bool> draw2={false,false,false};
    BOOST_CHECK_EQUAL(cast_action.countSuccesses(draw1),3);
    BOOST_CHECK_EQUAL(cast_action.countSuccesses(draw2),0);
}

BOOST_AUTO_TEST_CASE(CastAction_execute_test)
{
    state::GameState state;
    state::PlayablePawn sorcerer(state::Color::Red,state::Position(0,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer,&spell);

    // test when not on star tile and spell not null
    sorcerer.set_position(state::Position(1,-1));
    BOOST_CHECK_NO_THROW(cast_action.execute(state));

    // test when not on star tile and spell is null
    GameEngine::CastAction cast_action_null_spell(&sorcerer,nullptr);
    BOOST_CHECK_NO_THROW(cast_action_null_spell.execute(state));

    // test when on star tile and spell is null
    sorcerer.set_position(state::Position(2,-4));
    BOOST_CHECK_NO_THROW(cast_action_null_spell.execute(state));

    // test when on star tile and spell not null
    BOOST_CHECK_NO_THROW(cast_action.execute(state));
    
}

BOOST_AUTO_TEST_CASE(CastAction_resolve_draw_test)
{
    state::GameState state;
    state::PlayablePawn sorcerer(state::Color::Red, state::Position(0,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer, &spell);

    BOOST_CHECK(cast_action.resolve_draw({true}, state));
    BOOST_CHECK_EQUAL(spell.execution_count, 1);

    BOOST_CHECK(!cast_action.resolve_draw({false}, state));
    BOOST_CHECK_EQUAL(spell.execution_count, 1);

    GameEngine::CastAction cast_action_null(&sorcerer, nullptr);
    BOOST_CHECK(!cast_action_null.resolve_draw({true}, state));
}


BOOST_AUTO_TEST_CASE(CastAction_validate_test)
{
    state::PlayablePawn sorcerer(state::Color::Red,state::Position(0,0));
    TestSpell spell;
    GameEngine::CastAction cast_action(&sorcerer, &spell);
    state::GameState state;
    GameEngine::RuleEngine rules;

    BOOST_CHECK(!cast_action.validate(rules, state));
}
    