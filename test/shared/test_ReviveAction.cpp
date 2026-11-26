#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/ReviveAction.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/Sorcerer.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(ReviveAction_compilation_test)
{
    state::PlayablePawn warrior(state::Color::Red,state::Position(0,0));
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::ReviveAction action(&warrior,draw);
    (void)action;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(ReviveAction_can_apply_null_target_test)
{
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::ReviveAction action(nullptr,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(ReviveAction_can_apply_not_in_cimetery_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Camp);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::WARRIOR,state::Dice::WARRIOR};
    GameEngine::ReviveAction action(&warrior,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(ReviveAction_can_apply_warrior_2w_1t)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Cimetery);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::WARRIOR,state::Dice::TRISKELL};
    GameEngine::ReviveAction action(&warrior,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(ReviveAction_can_apply_sorcerer_3s)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Cimetery);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::SORCERER,state::Dice::SORCERER};
    GameEngine::ReviveAction action(&sorcerer,draw);
    BOOST_CHECK(action.can_apply());
}

BOOST_AUTO_TEST_CASE(ReviveAction_can_apply_sorcerer_invalid_draw_test)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Cimetery);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::ReviveAction action(&sorcerer,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(ReviveAction_can_apply_other_pawn_type_test)
{
    state::PlayablePawn pawn(state::Color::Red,state::Position(0,0));
    pawn.set_place(state::Place::Cimetery);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::ReviveAction action(&pawn,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(ReviveAction_execute_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Cimetery);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::WARRIOR,state::Dice::WARRIOR};
    GameEngine::ReviveAction action(&warrior,draw);
    state::GameState state;
    action.execute(state);
    BOOST_CHECK_EQUAL(warrior.get_place(),state::Place::Camp);
}

BOOST_AUTO_TEST_CASE(ReviveAction_execute_not_applicable)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Cimetery);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::SORCERER,state::Dice::SORCERER};
    GameEngine::ReviveAction action(&warrior,draw);
    state::GameState state;
    action.execute(state);
    BOOST_CHECK_EQUAL(warrior.get_place(),state::Place::Cimetery);
}

BOOST_AUTO_TEST_CASE(ReviveAction_validate_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::ReviveAction action(&warrior,draw);
    GameEngine::RuleEngine rules;
    state::GameState state;
    BOOST_CHECK(!action.validate(rules,state));
}