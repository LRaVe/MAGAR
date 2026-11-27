#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/Engine.h"
#include "../../src/shared/state/GameState.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(GameEngine_compilation_test)
{
    state::GameState state;
    (void)state;
    GameEngine::Engine engine;
    (void)engine;
    BOOST_CHECK(true); 
}

class DummyAction : public GameEngine::Action {
    public:
    void execute(state::GameState& state) override {}
    bool validate(GameEngine::RuleEngine& rules,state::GameState& state) override {return true;}
};

class InvalidAction : public GameEngine::Action {
    public:
    void execute(state::GameState& state) override {}
    bool validate(GameEngine::RuleEngine& rules,state::GameState& state) override {return true;}
};

BOOST_AUTO_TEST_CASE(GameEngine_start_game_test)
{
    state::GameState state;
    GameEngine::Engine engine;
    BOOST_CHECK_NO_THROW(engine.start_game());
}

BOOST_AUTO_TEST_CASE(GameEngine_start_turn_test)
{
    state::GameState state;
    GameEngine::Engine engine;
    BOOST_CHECK_NO_THROW(engine.start_turn());
}

BOOST_AUTO_TEST_CASE(GameEngine_submit_action_test)
{
    state::GameState state;
    GameEngine::Engine engine;
    DummyAction action;
    BOOST_CHECK_NO_THROW(engine.submit_action(action));

    // test with invalid action
    InvalidAction invalid_action;
    BOOST_CHECK_NO_THROW(engine.submit_action(invalid_action));
}

BOOST_AUTO_TEST_CASE(GameEngine_end_turn_test)
{
    state::GameState state;
    GameEngine::Engine engine;
    BOOST_CHECK_NO_THROW(engine.end_turn());
}

BOOST_AUTO_TEST_CASE(GameEngine_is_game_over_test)
{
    state::GameState state;
    GameEngine::Engine engine;
    BOOST_CHECK(!engine.is_game_over());
}