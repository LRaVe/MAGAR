#include "render/DiceLayer.h"

#include "state/GameState.h"
using namespace render;
#include <iostream>

DiceLayer::DiceLayer() {
    // Loading texture
    if(!G_texture.loadFromFile("assets/img/dice/j_face_g.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!M_texture.loadFromFile("assets/img/dice/j_face_m.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
    if(!T_texture.loadFromFile("assets/img/dice/j_face_t.png"))
        std::cerr << "Error: Could not load image!" << std::endl;
}

DiceLayer::~DiceLayer () = default;

void DiceLayer::render(sf::RenderWindow& window, state::GameState& state) {
    auto draw = state.get_draw_dice();
    for (int i = 0; i < static_cast<int>(draw.size()); i++) {
        sf::RectangleShape square;
        square.setPosition({static_cast<float>(-80+60*i),320});
        square.setSize({50,50});
        square.setTexture(&get_texture_from_dice(draw[i]));
        window.draw(square);
    }
}

const sf::Texture& DiceLayer::get_texture_from_dice(state::Dice dice) const {
    switch (dice)
    {
    case state::Dice::WARRIOR:
        return G_texture;
    case state::Dice::SORCERER:
        return M_texture;
    case state::Dice::TRISKELL:
        return T_texture;
    }
    return G_texture;
}
