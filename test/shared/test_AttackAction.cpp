#include <boost/test/unit_test.hpp>
#include "../../src/shared/GameEngine/AttackAction.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/state/AttackDice.h"
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/Sorcerer.h"
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(AttackAction_compilation_test)
{
    state::PlayablePawn attacker(state::Color::Red,state::Position(0,0));
    state::PlayablePawn target(state::Color::Blue,state::Position(1,0));
    GameEngine::AttackAction attack_action(&attacker,&target);
    (void)attack_action;
    BOOST_CHECK(true);
}

//BOOST_AUTO_TEST_CASE(AttackAction_areHexAdjacent_test)
//{
 //   state::Position pos1(0,0);
   // state::Position pos2(1,0);
    //state::Position pos3(2,0);
    //state::PlayablePawn attacker(state::Color::Red,pos1);
    //state::PlayablePawn target(state::Color::Blue,pos2);
    //GameEngine::AttackAction attack_action(&attacker,&target);
    //BOOST_CHECK(attack_action.areHexAdjacent(pos1,pos2));
    //BOOST_CHECK(!attack_action.areHexAdjacent(pos1,pos3));
//}

BOOST_AUTO_TEST_CASE(AttackAction_count_successes_test)
{
    state::PlayablePawn attacker(state::Color::Red,state::Position(0,0));
    state::PlayablePawn target(state::Color::Blue,state::Position(1,0));
    GameEngine::AttackAction attack_action(&attacker,&target);
    std::vector<bool> draw1 = {true, false, true, true};
    std::vector<bool> draw2 = {false, false, false};
    BOOST_CHECK_EQUAL(attack_action.countSuccesses(draw1), 3);
    BOOST_CHECK_EQUAL(attack_action.countSuccesses(draw2), 0);
}

BOOST_AUTO_TEST_CASE(AttackAction_execute_verification_test)
{
    // test if (!attacker || !target)
    GameEngine::AttackAction attack_action(nullptr,nullptr);
    state::GameState state;
    BOOST_CHECK_NO_THROW(attack_action.execute(state));
    state::PlayablePawn pawn1(state::Color::Red,state::Position(0,0));
    GameEngine::AttackAction attack_action2(nullptr,&pawn1);
    BOOST_CHECK_NO_THROW(attack_action2.execute(state));
    GameEngine::AttackAction attack_action3(&pawn1,nullptr);
    BOOST_CHECK_NO_THROW(attack_action3.execute(state));

    // test if attacker==target
    state::PlayablePawn pawn(state::Color::Red,state::Position(0,0));
    GameEngine::AttackAction attack_action4(&pawn,&pawn);
    BOOST_CHECK_NO_THROW(attack_action4.execute(state));

    // test if !areHexAdjacent(posAttacker,posTarget)
    state::PlayablePawn attacker(state::Color::Red,state::Position(0,0));
    state::PlayablePawn target(state::Color::Blue,state::Position(2,0));
    state::Position posAttacker = attacker.get_position();
    state::Position posTarget = target.get_position();
    GameEngine::AttackAction attack_action5(&attacker,&target);
    BOOST_CHECK(!attack_action5.is_target_adjacent());
    BOOST_CHECK_NO_THROW(attack_action5.execute(state));
}

BOOST_AUTO_TEST_CASE(AttackAction_resolve_combat_test)
{
    state::PlayablePawn attacker(state::Color::Red, state::Position(0,0));
    state::PlayablePawn target(state::Color::Blue, state::Position(1,0));
    GameEngine::AttackAction attack_action(&attacker, &target);

    attack_action.resolve_combat(2, 1);
    BOOST_CHECK_EQUAL(target.get_place(), state::Place::Hospital);

    target.set_place(state::Place::Arena);
    attack_action.resolve_combat(1, 2);
    BOOST_CHECK_EQUAL(attacker.get_place(), state::Place::Hospital);

    attacker.set_place(state::Place::Arena);
    target.set_place(state::Place::Arena);
    attack_action.resolve_combat(1, 1);
    BOOST_CHECK_EQUAL(attacker.get_place(), state::Place::Arena);
    BOOST_CHECK_EQUAL(target.get_place(), state::Place::Arena);
}

BOOST_AUTO_TEST_CASE(AttackAction_execute_combat_test)
{
    state::PlayablePawn attacker(state::Color::Red, state::Position(0,0));
    state::PlayablePawn target(state::Color::Blue, state::Position(1,0));
    attacker.set_attack(1);
    target.set_attack(1);

    GameEngine::AttackAction action(&attacker, &target);
    state::GameState state;

    BOOST_CHECK_NO_THROW(action.execute(state));
}


BOOST_AUTO_TEST_CASE(AttackAction_validate_test)
{
    state::PlayablePawn attacker(state::Color::Red, state::Position(0,0));
    state::PlayablePawn target(state::Color::Blue, state::Position(1,0));
    GameEngine::AttackAction action(&attacker, &target);
    state::GameState state;
    GameEngine::RuleEngine rules;

    BOOST_CHECK(!action.validate(rules, state));
}

BOOST_AUTO_TEST_CASE(AttackAction_class_dice_and_star_bonus_test)
{
    state::GameState game_state;
    state::Warrior& warrior = game_state.get_players()[0].get_warrior();
    state::Sorcerer& sorcerer = game_state.get_players()[0].get_sorcerer();

    BOOST_CHECK_EQUAL(GameEngine::AttackAction::dice_count_for(warrior, game_state), 2);
    BOOST_CHECK_EQUAL(GameEngine::AttackAction::dice_count_for(sorcerer, game_state), 1);

    warrior.set_position(state::Position(2, -4));
    sorcerer.set_position(state::Position(2, -4));
    BOOST_CHECK_EQUAL(GameEngine::AttackAction::dice_count_for(warrior, game_state), 3);
    BOOST_CHECK_EQUAL(GameEngine::AttackAction::dice_count_for(sorcerer, game_state), 2);
}

BOOST_AUTO_TEST_CASE(AttackAction_only_once_per_turn_test)
{
    state::GameState game_state;
    state::PlayablePawn& attacker = game_state.get_players()[0].get_warrior();
    state::PlayablePawn& target = game_state.get_players()[1].get_warrior();
    attacker.set_place(state::Place::Arena);
    target.set_place(state::Place::Arena);
    attacker.set_position(state::Position(0, 0));
    target.set_position(state::Position(1, 0));
    attacker.set_attack(1);
    target.set_attack(1);

    GameEngine::AttackAction action(&attacker, &target);
    GameEngine::RuleEngine rules;

    BOOST_CHECK(action.validate(rules, game_state));
    action.execute(game_state);
    BOOST_CHECK(game_state.has_attacked_this_turn());
    BOOST_CHECK(!action.validate(rules, game_state));

    game_state.next_turn();
    BOOST_CHECK(!game_state.has_attacked_this_turn());
}
