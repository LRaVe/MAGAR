#include  "render/BoardLayer.h"

#include <complex>

#include "state/CenterTile.h"
#include "state/ClassicTile.h"
#include "state/NestTile.h"
using namespace render;

#include <iostream>

#include "state/GameState.h"

constexpr float SIZE_HEXA = 35.f;

BoardLayer::BoardLayer() {
    // loading texture
    if(!center_texture.loadFromFile("assets/img/tiles/center_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!nest_texture.loadFromFile("assets/img/tiles/nest_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!classic_texture.loadFromFile("assets/img/tiles/classic_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!star_texture.loadFromFile("assets/img/tiles/star_tile.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
}

BoardLayer::~BoardLayer() = default;

void BoardLayer::render(sf::RenderWindow& window, state::GameState& state) {
    for (const auto& tile : state.get_board().get_tiles()) {
        draw_tile(window, tile);
    }
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
