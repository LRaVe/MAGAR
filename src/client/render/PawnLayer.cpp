#include "render/PawnLayer.h"

using namespace render;

#include <iostream>
#include <cmath>

#include "state/GameState.h"
#include "state/Dragon.h"

constexpr float SIZE_PAWN = 25.f;

PawnLayer::PawnLayer() {
    if(!dragon_texture.loadFromFile("assets/img/pawn/dragon.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
}

PawnLayer::~PawnLayer() = default;


void PawnLayer::render(sf::RenderWindow& window, state::GameState& state) {
    draw_dragon(window, state.get_dragon());
}

void PawnLayer::draw_dragon (sf::RenderWindow& window, state::Dragon& dragon){
    sf::CircleShape dragon_shape(SIZE_PAWN);

    auto pos = dragon.get_position();
    // Position Hex to pix
    auto x = static_cast<float>(std::sqrt(3) * pos.q + sqrt(3) / 2 * pos.r);
    auto y = static_cast<float>(3. / 2 * pos.r);
    x = x * SIZE_PAWN;
    y = y * SIZE_PAWN;
    dragon_shape.setPosition({x,y});
    dragon_shape.setOrigin({SIZE_PAWN, SIZE_PAWN}); // center
    dragon_shape.setTexture(&dragon_texture);

    window.draw(dragon_shape);
}
