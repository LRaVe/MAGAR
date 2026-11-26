#include  "render/BoardLayer.h"

#include "Transformator.h"
using namespace render;

#include "state/GameState.h"
#include "state/CenterTile.h"
#include "state/ClassicTile.h"
#include "state/NestTile.h"
#include "render/constant.hpp"

BoardLayer::BoardLayer() {
    // loading texture
    load_texture(center_texture, BOARD_ASSET_PATH + "center_tile.png");
    load_texture(nest_texture, BOARD_ASSET_PATH + "nest_tile.png");
    load_texture(classic_texture, BOARD_ASSET_PATH + "classic_tile.png");
    load_texture(star_texture, BOARD_ASSET_PATH + "star_tile.png");
    load_texture(camp_texture, BOARD_ASSET_PATH + "camp.png");
    load_texture(cemetery_texture, BOARD_ASSET_PATH + "cemetery.png");
    load_texture(hospital_texture, BOARD_ASSET_PATH + "hospital.png");
}

BoardLayer::~BoardLayer() = default;

void BoardLayer::render(sf::RenderWindow& window, state::GameState& state) {
    for (const auto& tile : state.get_board().get_tiles()) {
        draw_tile(window, tile);
    }
    for (auto camp : ALL_CAMP_PLACEMENT) {
        draw_element(window,camp.position,camp.rotation,camp.color,camp_texture,CAMP_SIZE);
    }
    for (auto hospital : ALL_HOSPITAL_PLACEMENT) {
        draw_element(window,hospital.position,hospital.rotation,hospital.color,hospital_texture,HOSPITAL_SIZE);
    }
    for (auto cemetery : ALL_CEMETERY_PLACEMENT) {
        draw_element(window,cemetery.position,cemetery.rotation,cemetery.color,cemetery_texture,CEMETERY_SIZE);
    }
}

void BoardLayer::draw_tile(sf::RenderWindow& window, const std::shared_ptr<state::Tile>& tile) {
    sf::CircleShape hexagon(SIZE_HEXA, 6);

    hexagon.setPosition(Transformator::hex_to_pixel(tile->get_position()));
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

void BoardLayer::draw_element(sf::RenderWindow& window, sf::Vector2f position, float rotation, state::Color color, sf::Texture& texture, float size) {
    sf::RectangleShape background;
    background.setSize({size, size});
    background.setOrigin({size/2, size/2});
    background.setPosition(position);
    background.setRotation(rotation);
    background.setFillColor(Transformator::to_sf_color(color));
    window.draw(background);

    sf::RectangleShape element;
    element.setSize({size,size});
    element.setOrigin({size/2,size/2});
    element.setPosition(position);
    element.setTexture(&texture);
    element.setRotation(rotation);
    window.draw(element);
}
