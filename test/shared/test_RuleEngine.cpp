#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(RuleEngine_compilation_test)
{
    GameEngine::RuleEngine rules;
    (void)rules;
    BOOST_CHECK(true);
}

class DummyAction : public GameEngine::Action {
    public:
    void execute (state::GameState& state) override {}
    bool validate (GameEngine::RuleEngine& rules,state::GameState& state) override {return true;}
};

BOOST_AUTO_TEST_CASE(RuleEngine_is_valid_test)
{
    GameEngine::RuleEngine rules;
    state::GameState state;
    DummyAction action;
    BOOST_CHECK_NO_THROW(rules.is_valid(state,action));
}

BOOST_AUTO_TEST_CASE(RuleEngine_possible_actions_heal_test)
{
    GameEngine::RuleEngine rules;
    state::GameState state;
    BOOST_CHECK_NO_THROW(rules.possible_actions(state));

    // if pawn->get_place() ==Place::Hospital and can_heal(pawn,state)==true
    state.set_draw({state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL});
    state.get_current_player().get_warrior().set_place(state::Place::Hospital);
    BOOST_CHECK_NO_THROW(rules.possible_actions(state));

    state.set_draw({state::Dice::TRISKELL,state::Dice::TRISKELL,state::Dice::TRISKELL});
    BOOST_CHECK_NO_THROW(rules.possible_actions(state));
}

BOOST_AUTO_TEST_CASE(RuleEngine_possible_actions_revive_test)
{
    GameEngine::RuleEngine rules;
    state::GameState state;
    
    // if pawn->get_place()==Place::Cimetery and can_revive==true
    state.get_current_player().get_warrior().set_place(state::Place::Cimetery);
    state.set_draw({state::Dice::WARRIOR,state::Dice::WARRIOR,state::Dice::WARRIOR});
    BOOST_CHECK_NO_THROW(rules.possible_actions(state));

    state.set_draw({state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL});
    BOOST_CHECK_NO_THROW(rules.possible_actions(state));
}

BOOST_AUTO_TEST_CASE(RuleEngine_can_move_test)
{
}

BOOST_AUTO_TEST_CASE(RuleEngine_can_attack_test)
{
    
}

BOOST_AUTO_TEST_CASE(RuleEngine_can_cast_test)
{}

