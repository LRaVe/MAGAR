#include "render/PawnLayer.h"

#include <iostream>
using namespace render;

#include "state/GameState.h"
#include "state/Dragon.h"
#include "render/Transformator.h"
#include "render/constant.hpp"

PawnLayer::PawnLayer() {
    load_texture(dragon_texture, PAWN_ASSET_PATH + "dragon.png");
    load_texture(stone_texture,PAWN_ASSET_PATH + "stone.png");
    load_texture(mage_red_texture, PAWN_ASSET_PATH + "mage_red.png");
    load_texture(warrior_red_texture, PAWN_ASSET_PATH + "warrior_red.png");
    load_texture(mage_blue_texture, PAWN_ASSET_PATH + "mage_blue.png");
    load_texture(warrior_blue_texture, PAWN_ASSET_PATH + "warrior_blue.png");
    load_texture(mage_green_texture, PAWN_ASSET_PATH + "mage_green.png");
    load_texture(warrior_green_texture, PAWN_ASSET_PATH + "warrior_green.png");
    load_texture(mage_yellow_texture, PAWN_ASSET_PATH + "mage_yellow.png");
    load_texture(warrior_yellow_texture, PAWN_ASSET_PATH + "warrior_yellow.png");
}

PawnLayer::~PawnLayer() = default;

void PawnLayer::render(sf::RenderWindow& window, state::GameState& state) {
    draw_dragon(window, state.get_dragon());
    for (auto& player : state.get_players()) {
        draw_playable(window, player.get_warrior(), 0);
        draw_playable(window, player.get_sorcerer(), 1);
    }
    draw_stone(window, state.get_stone(), state.stone_is_on());
}

void PawnLayer::draw_dragon (sf::RenderWindow& window, state::Dragon& dragon){
    sf::CircleShape dragon_shape(SIZE_PAWN);

    dragon_shape.setPosition(Transformator::hex_to_pixel(dragon.get_position()));
    dragon_shape.setOrigin({SIZE_PAWN, SIZE_PAWN}); // center
    dragon_shape.setTexture(&dragon_texture);

    window.draw(dragon_shape);
}

void PawnLayer::draw_stone (sf::RenderWindow& window, state::Stone& stone, bool is_on){
    float stone_size = is_on ? SIZE_PAWN/1.5 : SIZE_PAWN;

    sf::CircleShape stone_shape(stone_size);

    sf::Vector2f stone_position = is_on ? Transformator::hex_to_pixel(stone.get_position()) + sf::Vector2f({stone_size/2,stone_size/2})
                                        : Transformator::hex_to_pixel(stone.get_position());

    stone_shape.setPosition(stone_position);
    stone_shape.setOrigin({stone_size, stone_size}); // center
    stone_shape.setTexture(&stone_texture);

    window.draw(stone_shape);
}

sf::Vector2f get_position_from(std::array<Placement, 4> ALL_PLACEMENT, state::Color pawn_color ) {
    sf::Vector2f pos = {0,0};
    for (auto camp : ALL_PLACEMENT) {
        if (pawn_color == camp.color) {
            pos =  camp.position;
        }
    }
    return pos;
}

sf::Texture& PawnLayer::get_mage_texture_from(state::Color pawn_color) {
    switch (pawn_color) {
    case state::Color::Red:
        return mage_red_texture;
    case state::Color::Blue:
        return mage_blue_texture;
    case state::Color::Green:
        return mage_green_texture;
    case state::Color::Yellow:
        return mage_yellow_texture;
    }
    return mage_yellow_texture;
}

sf::Texture& PawnLayer::get_warrior_texture_from(state::Color pawn_color) {
    switch (pawn_color) {
    case state::Color::Red:
        return warrior_red_texture;
    case state::Color::Blue:
        return warrior_blue_texture;
    case state::Color::Green:
        return warrior_green_texture;
    case state::Color::Yellow:
        return warrior_yellow_texture;
    }
    return warrior_red_texture;
}

sf::Texture& PawnLayer::get_texture_from(state::PlayablePawn& pawn) {
    if (dynamic_cast<state::Warrior*>(&pawn))
        return get_warrior_texture_from(pawn.get_color());
    return get_mage_texture_from(pawn.get_color());
}

void PawnLayer::draw_playable(sf::RenderWindow& window, state::PlayablePawn& pawn, int slot) {
    sf::CircleShape pawn_shape(SIZE_PAWN);

    sf::Vector2f pawn_positon;

    switch (pawn.get_place()) {
    case state::Place::Arena :
        pawn_positon = Transformator::hex_to_pixel(pawn.get_position());
        break;
    case state::Place::Camp:
        pawn_positon = get_position_from(ALL_CAMP_PLACEMENT,pawn.get_color()) ;
        break;
    case state::Place::Hospital:
        pawn_positon = get_position_from(ALL_HOSPITAL_PLACEMENT,pawn.get_color());
        break;
    case state::Place::Cimetery:
        pawn_positon = get_position_from(ALL_CEMETERY_PLACEMENT,pawn.get_color());
        break;
    }
    if (pawn.get_place() != state::Place::Arena)
        pawn_positon += sf::Vector2f(slot == 0 ? -SLOT_OFFSET : SLOT_OFFSET, 0.f);



    pawn_shape.setPosition(pawn_positon);
    pawn_shape.setOrigin({SIZE_PAWN, SIZE_PAWN});
    pawn_shape.setTexture(&get_texture_from(pawn));
    window.draw(pawn_shape);
}
