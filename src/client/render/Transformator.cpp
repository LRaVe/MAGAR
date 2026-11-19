#include "render/Transformator.h"
using namespace render;

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>

/*
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
*/

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



