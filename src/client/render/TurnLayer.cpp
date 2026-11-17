#include "render/TurnLayer.h"
using namespace render;

#include <iostream>

#include "state/GameState.h"

TurnLayer::TurnLayer(){
    if (!title_font.loadFromFile( "assets/fonts/PirataOne.ttf")) {
        std::cerr << "Police not found\n";
    }
}

TurnLayer::~TurnLayer () = default;

void TurnLayer::render(sf::RenderWindow& window,state::GameState& state) {
    turn_draw(window, state.get_turn());
    current_color_draw(window, state.get_current_player().getColor());
}

void TurnLayer::turn_draw(sf::RenderWindow& window, int turn) const {
    // Turn Number
    sf::String turn_string = sf::String("Tour: ") + sf::String(std::to_string(turn));
    sf::Text turn_text(turn_string,title_font);
    turn_text.setFillColor( sf::Color::Black );
    turn_text.setCharacterSize( 25 );
    turn_text.setPosition({-590,-390});
    window.draw(turn_text);

}

void TurnLayer::current_color_draw(sf::RenderWindow& window, state::Color current_player_color) const {

    // Who's turn
    sf::String player_string;
    switch (current_player_color)
    {
    case state::Color::Red:
        player_string = sf::String("Red");
        break;
    case state::Color::Blue:
        player_string = sf::String("Blue");
        break;
    case state::Color::Green:
        player_string = sf::String("Green");
        break;
    case state::Color::Yellow:
        player_string = sf::String("Yellow");
        break;
    }
    sf::Text player_text(player_string,title_font);
    player_text.setFillColor( sf::Color::Black );
    player_text.setCharacterSize( 25 );
    player_text.setPosition({-590,-355});
    window.draw(player_text);
}
