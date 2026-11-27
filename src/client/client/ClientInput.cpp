#include <algorithm>
#include <cmath>
#include <iostream>

#include "GameEngine/Action.h"
#include "GameEngine/AttackAction.h"
#include "GameEngine/EndTurnAction.h"
#include "GameEngine/Engine.h"
#include "GameEngine/HealAction.h"
#include "GameEngine/MoveAction.h"
#include "GameEngine/ReviveAction.h"
#include "render/Transformator.h"
#include "render/constant.hpp"
#include "state/Board.h"
#include "state/Dragon.h"
#include "state/GameState.h"
#include "state/Pawn.h"
#include "state/Player.h"
#include "state/PlayablePawn.h"
#include "state/Tile.h"
#include "state/Warrior.h"
#include "client/ClientInput.h"

namespace {
constexpr float BUTTON_WIDTH = 124.f;
constexpr float BUTTON_HEIGHT = 36.f;
constexpr float BUTTON_GAP = 8.f;
constexpr float FIRST_BUTTON_X = -350.f;
constexpr float BUTTON_Y = -385.f;
constexpr float PAWN_HIT_RADIUS = render::SIZE_PAWN + 8.f;

bool same_position(const state::Position& lhs, const state::Position& rhs)
{
    return lhs.q == rhs.q && lhs.r == rhs.r;
}

int pawn_slot(state::PlayablePawn& pawn)
{
    return dynamic_cast<state::Warrior*>(&pawn) ? 0 : 1;
}

sf::Vector2f pawn_to_pixel(state::Pawn& pawn)
{
    if (state::PlayablePawn* playable = pawn.as_playable()) {
        return render::Transformator::playable_pawn_to_pixel(
            *playable, pawn_slot(*playable));
    }
    if (state::Dragon* dragon = dynamic_cast<state::Dragon*>(&pawn)) {
        return render::Transformator::hex_to_pixel(dragon->get_position());
    }
    return {};
}
}

namespace client {

namespace {
constexpr std::array<ActionType, 4> ACTION_TYPES = {
    ActionType::Move,
    ActionType::Attack,
    ActionType::Heal,
    ActionType::Revive
};
constexpr const char* ACTION_LABELS[] = {
    "Deplacer",
    "Attaquer",
    "Soigner",
    "Ressusciter"
};
}

ClientInput::ClientInput(sf::RenderWindow& window, GameEngine::Engine& engine)
    : window(window),
      engine(engine),
      action_buttons{},
      end_turn_bounds(FIRST_BUTTON_X + 4.f * (BUTTON_WIDTH + BUTTON_GAP),
                      BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT),
      message("Choisissez un type d'action.")
{
    for (std::size_t i = 0; i < action_buttons.size(); ++i) {
        action_buttons[i] = sf::FloatRect(
            FIRST_BUTTON_X + static_cast<float>(i) * (BUTTON_WIDTH + BUTTON_GAP),
            BUTTON_Y,
            BUTTON_WIDTH,
            BUTTON_HEIGHT);
    }

    font_loaded = font.loadFromFile("assets/fonts/PirataOne.ttf");
    if (!font_loaded) {
        std::cerr << "Impossible de charger assets/fonts/PirataOne.ttf\n";
    }
    refresh_actions();
}

ClientInput::~ClientInput() = default;

void ClientInput::handle_event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        selected_type.reset();
        selected_pawn = nullptr;
        message = "Choisissez un type d'action.";
        return;
    }

    if (event.type != sf::Event::MouseButtonPressed
        || event.mouseButton.button != sf::Mouse::Left) {
        return;
    }

    const sf::Vector2i pixel(event.mouseButton.x, event.mouseButton.y);
    const sf::Vector2f position = window.mapPixelToCoords(pixel);

    if (end_turn_bounds.contains(position)) {
        submit_end_turn();
        return;
    }

    for (std::size_t i = 0; i < action_buttons.size(); ++i) {
        if (!action_buttons[i].contains(position)) {
            continue;
        }
        const ActionType type = ACTION_TYPES[i];
        if (!has_actions(type)) {
            message = "Aucune action de ce type n'est disponible.";
            return;
        }
        selected_type = type;
        selected_pawn = nullptr;
        message = "Choisissez un pion.";
        return;
    }

    handle_click(position);
}

void ClientInput::render()
{
    draw_highlights();
    draw_buttons();
}

void ClientInput::refresh_actions()
{
    possible_actions = engine.possible_actions();
    selected_type.reset();
    selected_pawn = nullptr;
}

bool ClientInput::has_actions(ActionType type) const
{
    for (const auto& action : possible_actions) {
        if (type_for(action) == type) {
            return true;
        }
    }
    return false;
}

std::optional<ActionType> ClientInput::type_for(
    const std::shared_ptr<GameEngine::Action>& action) const
{
    if (std::dynamic_pointer_cast<GameEngine::MoveAction>(action)) {
        return ActionType::Move;
    }
    if (std::dynamic_pointer_cast<GameEngine::AttackAction>(action)) {
        return ActionType::Attack;
    }
    if (std::dynamic_pointer_cast<GameEngine::HealAction>(action)) {
        return ActionType::Heal;
    }
    if (std::dynamic_pointer_cast<GameEngine::ReviveAction>(action)) {
        return ActionType::Revive;
    }
    return std::nullopt;
}

state::Pawn* ClientInput::actor_for(
    const std::shared_ptr<GameEngine::Action>& action) const
{
    if (const auto move =
            std::dynamic_pointer_cast<GameEngine::MoveAction>(action)) {
        return move->get_pawn();
    }
    if (const auto attack =
            std::dynamic_pointer_cast<GameEngine::AttackAction>(action)) {
        return attack->get_attacker();
    }
    if (const auto heal =
            std::dynamic_pointer_cast<GameEngine::HealAction>(action)) {
        return heal->target;
    }
    if (const auto revive =
            std::dynamic_pointer_cast<GameEngine::ReviveAction>(action)) {
        return revive->target;
    }
    return nullptr;
}

std::vector<std::shared_ptr<GameEngine::Action>>
ClientInput::selected_actions() const
{
    std::vector<std::shared_ptr<GameEngine::Action>> result;
    if (!selected_type || !selected_pawn) {
        return result;
    }

    for (const auto& action : possible_actions) {
        if (type_for(action) == selected_type
            && actor_for(action) == selected_pawn) {
            result.push_back(action);
        }
    }
    return result;
}

void ClientInput::handle_click(sf::Vector2f position)
{
    if (!selected_type) {
        return;
    }

    if (selected_pawn) {
        for (const auto& action : selected_actions()) {
            if (is_action_target(action, position)) {
                submit_action(action);
                return;
            }
        }
    }

    state::Pawn* clicked_pawn = pawn_at(position);
    if (clicked_pawn) {
        const bool can_select = std::any_of(
            possible_actions.begin(),
            possible_actions.end(),
            [this, clicked_pawn](const auto& action) {
                return type_for(action) == selected_type
                    && actor_for(action) == clicked_pawn;
            });
        if (can_select) {
            selected_pawn = clicked_pawn;
            message = "Cliquez sur une cible surlignee.";
            return;
        }
    }

    selected_pawn = nullptr;
    message = "Choisissez un pion.";
}

void ClientInput::submit_action(
    const std::shared_ptr<GameEngine::Action>& action)
{
    if (!engine.submit_action(*action)) {
        message = "Cette action n'est plus valide.";
        refresh_actions();
        return;
    }
    refresh_actions();
    message = "Action effectuee. Choisissez un type d'action.";
}

void ClientInput::submit_end_turn()
{
    GameEngine::EndTurnAction action;
    if (!engine.submit_action(action)) {
        message = "Impossible de terminer le tour.";
        return;
    }
    refresh_actions();
    message = "Nouveau tour. Choisissez un type d'action.";
}

state::Pawn* ClientInput::pawn_at(sf::Vector2f position) const
{
    state::GameState& game_state = engine.state;
    state::Pawn* nearest = nullptr;
    float nearest_distance_squared = PAWN_HIT_RADIUS * PAWN_HIT_RADIUS;

    for (state::Player& player : game_state.get_players()) {
        state::PlayablePawn* pawns[] = {
            &player.get_warrior(),
            &player.get_sorcerer()
        };
        for (std::size_t slot = 0; slot < 2; ++slot) {
            state::PlayablePawn* pawn = pawns[slot];
            const sf::Vector2f pawn_position =
                render::Transformator::playable_pawn_to_pixel(
                    *pawn, static_cast<int>(slot));
            const float dx = position.x - pawn_position.x;
            const float dy = position.y - pawn_position.y;
            const float distance_squared = dx * dx + dy * dy;
            if (distance_squared <= nearest_distance_squared) {
                nearest = pawn;
                nearest_distance_squared = distance_squared;
            }
        }
    }

    state::Dragon& dragon = game_state.get_dragon();
    const sf::Vector2f dragon_position =
        render::Transformator::hex_to_pixel(dragon.get_position());
    const float dragon_dx = position.x - dragon_position.x;
    const float dragon_dy = position.y - dragon_position.y;
    const float dragon_distance_squared =
        dragon_dx * dragon_dx + dragon_dy * dragon_dy;
    if (dragon_distance_squared <= nearest_distance_squared) {
        nearest = &dragon;
    }

    return nearest;
}

std::optional<state::Position> ClientInput::board_position_at(
    sf::Vector2f position) const
{
    state::GameState& game_state = engine.state;
    std::optional<state::Position> nearest;
    float nearest_distance_squared = render::SIZE_HEXA * render::SIZE_HEXA;

    for (const auto& tile : game_state.get_board().get_tiles()) {
        const sf::Vector2f tile_position =
            render::Transformator::hex_to_pixel(tile->get_position());
        const float dx = position.x - tile_position.x;
        const float dy = position.y - tile_position.y;
        const float distance_squared = dx * dx + dy * dy;
        if (distance_squared <= nearest_distance_squared) {
            nearest = tile->get_position();
            nearest_distance_squared = distance_squared;
        }
    }
    return nearest;
}

bool ClientInput::is_action_target(
    const std::shared_ptr<GameEngine::Action>& action,
    sf::Vector2f position) const
{
    if (const auto move =
            std::dynamic_pointer_cast<GameEngine::MoveAction>(action)) {
        const auto clicked_position = board_position_at(position);
        return clicked_position
            && same_position(*clicked_position, move->get_destination());
    }

    if (const auto attack =
            std::dynamic_pointer_cast<GameEngine::AttackAction>(action)) {
        return pawn_at(position) == attack->get_target();
    }

    if (const auto heal =
            std::dynamic_pointer_cast<GameEngine::HealAction>(action)) {
        return pawn_at(position) == heal->target;
    }

    if (const auto revive =
            std::dynamic_pointer_cast<GameEngine::ReviveAction>(action)) {
        return pawn_at(position) == revive->target;
    }

    return false;
}

void ClientInput::draw_buttons()
{
    for (std::size_t i = 0; i < action_buttons.size(); ++i) {
        const sf::FloatRect& bounds = action_buttons[i];
        const ActionType type = ACTION_TYPES[i];
        const bool available = has_actions(type);
        const bool selected = selected_type == type;
        sf::RectangleShape shape(
            {bounds.width, bounds.height});
        shape.setPosition({bounds.left, bounds.top});
        shape.setFillColor(!available
            ? sf::Color(120, 120, 120)
            : selected ? sf::Color(60, 110, 175) : sf::Color(65, 75, 90));
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color::Black);
        window.draw(shape);

        if (font_loaded) {
            sf::Text text(ACTION_LABELS[i], font);
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::White);
            text.setPosition(bounds.left + 8.f,
                             bounds.top + 8.f);
            window.draw(text);
        }
    }

    sf::RectangleShape end_turn(
        {end_turn_bounds.width, end_turn_bounds.height});
    end_turn.setPosition({end_turn_bounds.left, end_turn_bounds.top});
    end_turn.setFillColor(sf::Color(120, 75, 65));
    end_turn.setOutlineThickness(1.f);
    end_turn.setOutlineColor(sf::Color::Black);
    window.draw(end_turn);

    if (font_loaded) {
        sf::Text end_turn_text("Fin du tour", font);
        end_turn_text.setCharacterSize(16);
        end_turn_text.setFillColor(sf::Color::White);
        end_turn_text.setPosition(end_turn_bounds.left + 8.f,
                                  end_turn_bounds.top + 8.f);
        window.draw(end_turn_text);

        sf::Text status(message, font);
        status.setCharacterSize(16);
        status.setFillColor(sf::Color::Black);
        status.setPosition(FIRST_BUTTON_X, BUTTON_Y + BUTTON_HEIGHT + 8.f);
        window.draw(status);
    }
}

void ClientInput::draw_highlights()
{
    if (!selected_type || !selected_pawn) {
        return;
    }

    sf::CircleShape selected_ring(render::SIZE_PAWN + 5.f);
    selected_ring.setOrigin({render::SIZE_PAWN + 5.f,
                             render::SIZE_PAWN + 5.f});
    selected_ring.setPosition(pawn_to_pixel(*selected_pawn));
    selected_ring.setFillColor(sf::Color::Transparent);
    selected_ring.setOutlineThickness(3.f);
    selected_ring.setOutlineColor(sf::Color(40, 100, 235));
    window.draw(selected_ring);

    const auto draw_pawn_target = [this](state::Pawn* pawn,
                                         sf::Color color) {
        if (!pawn) {
            return;
        }
        const float radius = render::SIZE_PAWN + 7.f;
        sf::CircleShape target(radius);
        target.setOrigin({radius, radius});
        target.setPosition(pawn_to_pixel(*pawn));
        target.setFillColor(sf::Color::Transparent);
        target.setOutlineThickness(4.f);
        target.setOutlineColor(color);
        window.draw(target);
    };

    for (const auto& action : selected_actions()) {
        if (const auto move =
                std::dynamic_pointer_cast<GameEngine::MoveAction>(action)) {
            sf::CircleShape destination(render::SIZE_HEXA, 6);
            destination.setOrigin({render::SIZE_HEXA, render::SIZE_HEXA});
            destination.setPosition(render::Transformator::hex_to_pixel(
                move->get_destination()));
            destination.setFillColor(sf::Color(255, 215, 0, 70));
            destination.setOutlineThickness(4.f);
            destination.setOutlineColor(sf::Color(235, 165, 0));
            window.draw(destination);
        } else if (const auto attack =
                       std::dynamic_pointer_cast<GameEngine::AttackAction>(
                           action)) {
            draw_pawn_target(attack->get_target(), sf::Color(220, 45, 45));
        } else if (const auto heal =
                       std::dynamic_pointer_cast<GameEngine::HealAction>(
                           action)) {
            draw_pawn_target(heal->target, sf::Color(40, 170, 80));
        } else if (const auto revive =
                       std::dynamic_pointer_cast<GameEngine::ReviveAction>(
                           action)) {
            draw_pawn_target(revive->target, sf::Color(135, 80, 190));
        }
    }
}

}
