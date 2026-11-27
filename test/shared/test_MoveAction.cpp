#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <array>
#include "../../src/shared/GameEngine/MoveAction.h"
#include "../../src/shared/GameEngine/Engine.h"
#include "../../src/shared/state/PlayablePawn.h"
#include "../../src/shared/state/Warrior.h"
#include "../../src/shared/state/Sorcerer.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/GameEngine/RuleEngine.h"

BOOST_AUTO_TEST_CASE(MoveAction_compilation_test)
{
    state::PlayablePawn pawn(state::Color::Red,state::Position(0,0));
    state::Position destination(1,0);
    GameEngine::MoveAction action(&pawn,destination);
    (void)action;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(MoveAction_can_apply_null_target_test)
{
    state::Position destination(1,0);
    GameEngine::MoveAction action(nullptr,destination);
    state::GameState state;
    BOOST_CHECK(!action.can_apply(state));
}

BOOST_AUTO_TEST_CASE(MoveAction_can_apply_not_in_arena_test)
{
    
}

BOOST_AUTO_TEST_CASE(MoveAction_camp_entry_destination_test)
{
    state::GameState game_state;
    state::PlayablePawn& pawn = game_state.get_players()[0].get_warrior();
    const auto entries =
        GameEngine::RuleEngine::camp_entries_for(state::Color::Red);
    BOOST_REQUIRE(entries);
    const state::Position entry = entries->front();
    GameEngine::MoveAction action(&pawn, entry);

    BOOST_CHECK(action.is_pawn_eligible(game_state));
    BOOST_CHECK(action.is_destination_valid(game_state));

    const auto other_entries =
        GameEngine::RuleEngine::camp_entries_for(state::Color::Blue);
    BOOST_REQUIRE(other_entries);
    GameEngine::MoveAction wrong_destination(&pawn, other_entries->front());
    BOOST_CHECK(!wrong_destination.is_destination_valid(game_state));
}

BOOST_AUTO_TEST_CASE(MoveAction_camp_entry_possible_and_applied_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);

    GameEngine::RuleEngine rules;
    const auto actions = rules.possible_actions(game_state);
    state::PlayablePawn& pawn = game_state.get_players()[0].get_warrior();
    const auto entry_action = std::find_if(
        actions.begin(),
        actions.end(),
        [&pawn](const auto& action) {
            const auto move =
                std::dynamic_pointer_cast<GameEngine::MoveAction>(action);
            return move && move->get_pawn() == &pawn;
        });
    BOOST_REQUIRE(entry_action != actions.end());

    GameEngine::Engine engine(game_state);
    BOOST_CHECK(engine.submit_action(**entry_action));
    BOOST_CHECK_EQUAL(pawn.get_place(), state::Place::Arena);

    const auto move =
        std::dynamic_pointer_cast<GameEngine::MoveAction>(*entry_action);
    BOOST_REQUIRE(move);
    const state::Position expected = move->get_destination();
    BOOST_CHECK_EQUAL(pawn.get_position().q, expected.q);
    BOOST_CHECK_EQUAL(pawn.get_position().r, expected.r);
}

BOOST_AUTO_TEST_CASE(MoveAction_generates_four_camp_entries_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);

    GameEngine::RuleEngine rules;
    const auto actions = rules.possible_actions(game_state);
    const auto entries =
        GameEngine::RuleEngine::camp_entries_for(state::Color::Red);
    BOOST_REQUIRE(entries);

    state::PlayablePawn& pawn = game_state.get_players()[0].get_warrior();
    for (const state::Position& entry : *entries) {
        const auto action = std::find_if(
            actions.begin(),
            actions.end(),
            [&pawn, &entry](const auto& candidate) {
                const auto move =
                    std::dynamic_pointer_cast<GameEngine::MoveAction>(candidate);
                return move
                    && move->get_pawn() == &pawn
                    && move->get_destination().q == entry.q
                    && move->get_destination().r == entry.r;
            });
        BOOST_CHECK(action != actions.end());
    }
}

BOOST_AUTO_TEST_CASE(MoveAction_blocks_occupied_entry_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);
    const auto entries =
        GameEngine::RuleEngine::camp_entries_for(state::Color::Red);
    BOOST_REQUIRE(entries);

    state::PlayablePawn& pawn = game_state.get_players()[0].get_warrior();
    state::PlayablePawn& blocker = game_state.get_players()[1].get_warrior();
    blocker.set_place(state::Place::Arena);
    blocker.set_position(entries->front());
    GameEngine::MoveAction action(&pawn, entries->front());

    BOOST_CHECK(!action.can_apply(game_state));
}

BOOST_AUTO_TEST_CASE(MoveAction_dragon_captures_in_nest_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);
    state::Dragon& dragon = game_state.get_dragon();
    dragon.set_position(state::Position(0, 0));
    state::PlayablePawn& target = game_state.get_players()[1].get_warrior();
    target.set_place(state::Place::Arena);
    target.set_position(state::Position(1, 0));

    GameEngine::MoveAction action(&dragon, state::Position(1, 0));
    BOOST_REQUIRE(action.can_apply(game_state));
    action.execute(game_state);

    BOOST_CHECK_EQUAL(target.get_place(), state::Place::Cimetery);
}

BOOST_AUTO_TEST_CASE(MoveAction_dragon_wounds_outside_nest_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);
    state::Dragon& dragon = game_state.get_dragon();
    dragon.set_position(state::Position(2, 0));
    state::PlayablePawn& target = game_state.get_players()[1].get_warrior();
    target.set_place(state::Place::Arena);
    target.set_position(state::Position(3, 0));

    GameEngine::MoveAction action(&dragon, state::Position(3, 0));
    BOOST_REQUIRE(action.can_apply(game_state));
    action.execute(game_state);

    BOOST_CHECK_EQUAL(target.get_place(), state::Place::Hospital);
}

BOOST_AUTO_TEST_CASE(MoveAction_dragon_wounds_on_center_tile_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);
    state::Dragon& dragon = game_state.get_dragon();
    dragon.set_position(state::Position(1, 0));
    state::PlayablePawn& target = game_state.get_players()[1].get_warrior();
    target.set_place(state::Place::Arena);
    target.set_position(state::Position(0, 0));

    GameEngine::MoveAction action(&dragon, state::Position(0, 0));
    BOOST_REQUIRE(action.can_apply(game_state));
    action.execute(game_state);

    BOOST_CHECK_EQUAL(target.get_place(), state::Place::Hospital);
}

BOOST_AUTO_TEST_CASE(MoveAction_dragon_cannot_land_on_star_test)
{
    state::GameState game_state;
    game_state.get_draw_dice().roll(256);
    state::Dragon& dragon = game_state.get_dragon();
    const auto tiles = game_state.get_board().get_tiles();
    const auto star = std::find_if(
        tiles.begin(),
        tiles.end(),
        [](const auto& tile) { return tile->is_star_tile(); });
    BOOST_REQUIRE(star != tiles.end());

    const state::Position destination = (*star)->get_position();
    const std::array<state::Position, 6> adjacent_positions = {{
        state::Position(destination.q - 1, destination.r),
        state::Position(destination.q + 1, destination.r),
        state::Position(destination.q, destination.r - 1),
        state::Position(destination.q, destination.r + 1),
        state::Position(destination.q - 1, destination.r + 1),
        state::Position(destination.q + 1, destination.r - 1)
    }};
    const auto adjacent = std::find_if(
        adjacent_positions.begin(),
        adjacent_positions.end(),
        [&destination](const state::Position& position) {
            return position.is_in_radius(5)
                && position.is_adjacent_to(destination);
        });
    BOOST_REQUIRE(adjacent != adjacent_positions.end());

    dragon.set_position(*adjacent);
    GameEngine::MoveAction action(&dragon, destination);

    BOOST_CHECK(!action.is_destination_valid(game_state));
    BOOST_CHECK(!action.can_apply(game_state));
}

BOOST_AUTO_TEST_CASE(MoveAction_only_dragon_uses_triskell_test)
{
    state::GameState game_state;
    state::DrawDice& dice = game_state.get_draw_dice();
    dice.roll(256);
    BOOST_REQUIRE(dice.has_dice(state::TRISKELL));
    while (dice.consume_dice(state::WARRIOR)) {}
    while (dice.consume_dice(state::SORCERER)) {}

    GameEngine::RuleEngine rules;
    const auto actions = rules.possible_actions(game_state);
    int dragon_moves = 0;
    int playable_moves = 0;
    for (const auto& action : actions) {
        const auto move =
            std::dynamic_pointer_cast<GameEngine::MoveAction>(action);
        if (!move) {
            continue;
        }
        if (dynamic_cast<state::Dragon*>(move->get_pawn())) {
            ++dragon_moves;
        } else {
            ++playable_moves;
        }
    }

    BOOST_CHECK_GT(dragon_moves, 0);
    BOOST_CHECK_EQUAL(playable_moves, 0);

    while (dice.consume_dice(state::TRISKELL)) {}
    const auto actions_without_triskell = rules.possible_actions(game_state);
    for (const auto& action : actions_without_triskell) {
        const auto move =
            std::dynamic_pointer_cast<GameEngine::MoveAction>(action);
        BOOST_CHECK(!move || !dynamic_cast<state::Dragon*>(move->get_pawn()));
    }
}
