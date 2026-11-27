#include "render/Transformator.h"

#include <cmath>

#include "state/Position.h"
#include "state/PlayablePawn.h"
using namespace render;

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>
#include "render/constant.hpp"

sf::Color Transformator::to_sf_color(state::Color color)
{
    sf::Color result;
    switch (color)
    {
    case state::Color::Red:
        result = sf::Color::Red;
        break;
    case state::Color::Blue:
        result = sf::Color::Blue;
        break;
    case state::Color::Green:
        result = sf::Color::Green;
        break;
    case state::Color::Yellow:
        result = sf::Color::Yellow;
        break;
    }
    return result;
}


sf::String Transformator::to_sf_string(state::Color color)
{
    sf::String result;
    switch (color)
    {
    case state::Color::Red:
        result = sf::String("Red");
        break;
    case state::Color::Blue:
        result = sf::String("Blue");
        break;
    case state::Color::Green:
        result = sf::String("Green");
        break;
    case state::Color::Yellow:
        result = sf::String("Yellow");
        break;
    }
    return result;
}

std::string Transformator::to_string(state::Color color)
{
    std::string result;
    switch (color)
    {
    case state::Color::Red:
        result = sf::String("red");
        break;
    case state::Color::Blue:
        result = sf::String("blue");
        break;
    case state::Color::Green:
        result = sf::String("green");
        break;
    case state::Color::Yellow:
        result = sf::String("yellow");
        break;
    }
    return result;
}

static sf::Vector2f get_position_from(
    const std::array<Placement, 4>& placements,
    state::Color pawn_color)
{
    for (const auto& placement : placements) {
        if (pawn_color == placement.color) {
            return placement.position;
        }
    }
    return {0.f, 0.f};
}

sf::Vector2f Transformator::hex_to_pixel(const state::Position& pos) {
    auto x = static_cast<float>(sqrt(3) * pos.q + std::sqrt(3) / 2 * pos.r);
    auto y = static_cast<float>(3. / 2 * pos.r);
    x = x * SIZE_HEXA;
    y = y * SIZE_HEXA;
    return {x,y};
}

sf::Vector2f Transformator::playable_pawn_to_pixel(
    state::PlayablePawn& pawn,
    int slot)
{
    sf::Vector2f position;
    switch (pawn.get_place()) {
    case state::Place::Arena:
        return hex_to_pixel(pawn.get_position());
    case state::Place::Camp:
        position = get_position_from(ALL_CAMP_PLACEMENT, pawn.get_color());
        break;
    case state::Place::Hospital:
        position = get_position_from(ALL_HOSPITAL_PLACEMENT, pawn.get_color());
        break;
    case state::Place::Cimetery:
        position = get_position_from(ALL_CEMETERY_PLACEMENT, pawn.get_color());
        break;
    }

    position += sf::Vector2f(slot == 0 ? -SLOT_OFFSET : SLOT_OFFSET, 0.f);
    return position;
}

