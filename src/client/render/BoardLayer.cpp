#include  "render/BoardLayer.h"
using namespace render;

#include <iostream>
#include <cmath>

#include "state/GameState.h"
#include "state/CenterTile.h"
#include "state/ClassicTile.h"
#include "state/NestTile.h"

constexpr float SIZE_HEXA = 35.f;

BoardLayer::BoardLayer() {
    // loading texture
    if(!center_texture.loadFromFile("assets/img/board/center_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!nest_texture.loadFromFile("assets/img/board/nest_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!classic_texture.loadFromFile("assets/img/board/classic_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!star_texture.loadFromFile("assets/img/board/star_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if (!camp_texture.loadFromFile("assets/img/board/camp.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if (!cemetery_texture.loadFromFile("assets/img/board/cemetery.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if (!hospital_texture.loadFromFile("assets/img/board/hospital.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
}

BoardLayer::~BoardLayer() = default;

void BoardLayer::render(sf::RenderWindow& window, state::GameState& state) {
    for (const auto& tile : state.get_board().get_tiles()) {
        draw_tile(window, tile);
    }
    draw_all_camp(window);
    draw_all_hospital(window);
    draw_all_cemetery(window);
}

void BoardLayer::draw_tile(sf::RenderWindow& window, const std::shared_ptr<state::Tile>& tile) {
    sf::CircleShape hexagon(SIZE_HEXA, 6);

    auto pos = tile->get_position();
    // Position Hex to pix
    auto x = static_cast<float>(sqrt(3) * pos.q + sqrt(3) / 2 * pos.r);
    auto y = static_cast<float>(3. / 2 * pos.r);
    x = x * SIZE_HEXA;
    y = y * SIZE_HEXA;
    hexagon.setPosition({x,y});
    hexagon.setOrigin({SIZE_HEXA, SIZE_HEXA}); // center

    hexagon.setOutlineThickness(2.f);
    hexagon.setOutlineColor(sf::Color(20, 20, 20));

    hexagon.setTexture(&get_texture_from_tile(tile));

    window.draw(hexagon);
}

const sf::Texture& BoardLayer::get_texture_from_tile(const std::shared_ptr<state::Tile>& tile) const {
    auto res = classic_texture;
    if (std::dynamic_pointer_cast<state::CenterTile>(tile)) return center_texture;
    if (std::dynamic_pointer_cast<state::NestTile>(tile)) return nest_texture;
    if (std::dynamic_pointer_cast<state::ClassicTile>(tile)) return classic_texture;
    // else
    return star_texture;
}


void BoardLayer::draw_all_camp(sf::RenderWindow& window) {
    draw_camp(window,{-270,-300},-45, sf::Color::Red);
    draw_camp(window,{270,-300},45, sf::Color::Blue);
    draw_camp(window,{-270,300},225, sf::Color::Green);
    draw_camp(window,{270,300},-225, sf::Color::Yellow);
}

void BoardLayer::draw_camp(sf::RenderWindow& window, sf::Vector2f position,float rotation, sf::Color color) {
    sf::RectangleShape background;
    background.setSize({150, 150});
    background.setOrigin({75, 75});
    background.setPosition(position);
    background.setRotation(rotation);
    background.setFillColor(color);
    window.draw(background);

    sf::RectangleShape camp;
    camp.setSize({150,150});
    camp.setOrigin({75,75});
    camp.setPosition(position);
    camp.setTexture(&camp_texture);
    camp.setRotation(rotation);
    window.draw(camp);
}

void BoardLayer::draw_all_hospital(sf::RenderWindow& window) {
    draw_hospital(window,{-375,-100},180, sf::Color::Red);
    draw_hospital(window,{375,-100},180, sf::Color::Blue);
    draw_hospital(window,{-375,100},0, sf::Color::Green);
    draw_hospital(window,{375,100},0, sf::Color::Yellow);
}

void BoardLayer::draw_hospital(sf::RenderWindow& window, sf::Vector2f position, float rotation, sf::Color color) {
    sf::RectangleShape background;
    background.setSize({100, 100});
    background.setOrigin({50, 50});
    background.setPosition(position);
    background.setRotation(rotation);
    background.setFillColor(color);
    window.draw(background);

    sf::RectangleShape hospital;
    hospital.setSize({100,100});
    hospital.setOrigin({50,50});
    hospital.setPosition(position);
    hospital.setTexture(&hospital_texture);
    hospital.setRotation(rotation);
    window.draw(hospital);
}

void BoardLayer::draw_all_cemetery(sf::RenderWindow& window) {
    draw_cemetery(window,{-120,-350},90, sf::Color::Red);
    draw_cemetery(window,{120,-350},-90, sf::Color::Blue);
    draw_cemetery(window,{-120,350},90, sf::Color::Green);
    draw_cemetery(window,{120,350},-90, sf::Color::Yellow);
}

void BoardLayer::draw_cemetery(sf::RenderWindow& window, sf::Vector2f position, float rotation, sf::Color color) {
    sf::RectangleShape background;
    background.setSize({100, 100});
    background.setOrigin({50, 50});
    background.setPosition(position);
    background.setRotation(rotation);
    background.setFillColor(color);
    window.draw(background);

    sf::RectangleShape cemetery;
    cemetery.setSize({100,100});
    cemetery.setOrigin({50,50});
    cemetery.setPosition(position);
    cemetery.setTexture(&cemetery_texture);
    cemetery.setRotation(rotation);
    window.draw(cemetery);
}
