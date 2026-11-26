#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/HealAction.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/Sorcerer.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(HealAction_compilation_test)
{
    state::PlayablePawn pawn(state::Color::Red,state::Position(0,0));
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&pawn,draw);
    (void)action;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_null_target_test)
{
    // null target
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(nullptr,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_not_in_hospital_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&warrior,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_warrior_1w_2t)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&warrior,draw);
    BOOST_CHECK(action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_warrior_2w_1t)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::WARRIOR,state::Dice::TRISKELL};
    GameEngine::HealAction action(&warrior,draw);
    BOOST_CHECK(action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_warrior_1w_1t_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::SORCERER};
    GameEngine::HealAction action(&warrior,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_warrior_2w_0t_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::WARRIOR,state::Dice::SORCERER};
    GameEngine::HealAction action(&warrior,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_warrior_invalid_draw_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&warrior,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_sorcerer_1s_2t)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&sorcerer,draw);
    BOOST_CHECK(action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_sorcerer_2s_1t)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::SORCERER,state::Dice::TRISKELL};
    GameEngine::HealAction action(&sorcerer,draw);
    BOOST_CHECK(action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_sorcerer_1s_1t_test)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::TRISKELL,state::Dice::WARRIOR};
    GameEngine::HealAction action(&sorcerer,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_sorcerer_2s_0t_test)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::SORCERER,state::Dice::WARRIOR};
    GameEngine::HealAction action(&sorcerer,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_sorcerer_invalid_draw_test)
{
    state::Sorcerer sorcerer(state::Color::Red,state::Position(0,0));
    sorcerer.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&sorcerer,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_execute_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&warrior,draw);
    state::GameState state;
    action.execute(state);
    BOOST_CHECK_EQUAL(warrior.get_place(),state::Place::Camp);
}

BOOST_AUTO_TEST_CASE(HealAction_execute_null_target_test)
{
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(nullptr,draw);
    state::GameState state;
    BOOST_CHECK_NO_THROW(action.execute(state));
}

BOOST_AUTO_TEST_CASE(HealAction_execute_not_applicable)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::SORCERER,state::Dice::SORCERER,state::Dice::SORCERER};
    GameEngine::HealAction action(&warrior,draw);
    state::GameState state;
    action.execute(state);
    BOOST_CHECK_EQUAL(warrior.get_place(),state::Place::Hospital);
}


BOOST_AUTO_TEST_CASE(HealAction_validate_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&warrior,draw);
    GameEngine::RuleEngine rules;
    state::GameState state;
    BOOST_CHECK(!action.validate(rules,state));
}

BOOST_AUTO_TEST_CASE(HealAction_can_apply_other_pawn_type_test)
{
    state::PlayablePawn pawn(state::Color::Red,state::Position(0,0));
    pawn.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    GameEngine::HealAction action(&pawn,draw);
    BOOST_CHECK(!action.can_apply());
}

BOOST_AUTO_TEST_CASE(HealAction_unique_ptr_destructor_test)
{
    state::Warrior warrior(state::Color::Red,state::Position(0,0));
    warrior.set_place(state::Place::Hospital);
    std::vector<state::Dice> draw={state::Dice::WARRIOR,state::Dice::TRISKELL,state::Dice::TRISKELL};
    std::unique_ptr<GameEngine::HealAction> action=std::make_unique<GameEngine::HealAction>(&warrior,draw);

    BOOST_CHECK(action);
    action.reset();
    BOOST_CHECK(!action);
}