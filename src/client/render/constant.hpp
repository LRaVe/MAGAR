#pragma once
#include <array>

#include "state/Color.h"

typedef struct  {
    sf::Vector2f position;
    float rotation;
    state::Color color;
} Placement;

namespace render {
    // Pawn Constant
    constexpr float SIZE_PAWN = 25.f;
    const std::string PAWN_ASSET_PATH = "assets/img/pawn/";

    // Tile Constant
    constexpr float SIZE_HEXA = 35.f;

    // Board Constant
    const std::string BOARD_ASSET_PATH = "assets/img/board/";
    const float SLOT_OFFSET = 15.f;
    constexpr float CAMP_SIZE = 150;
    const Placement CAMP_RED_PLACEMENT = {{-270,-300},-45, state::Color::Red};
    const Placement CAMP_BLUE_PLACEMENT = {{270,-300},45, state::Color::Blue};
    const Placement CAMP_GREEN_PLACEMENT = {{-270,300},225, state::Color::Green};
    const Placement CAMP_YELLOW_PLACEMENT = {{270,300},-225, state::Color::Yellow};
    const inline std::array ALL_CAMP_PLACEMENT = {
        CAMP_RED_PLACEMENT,
        CAMP_BLUE_PLACEMENT,
        CAMP_GREEN_PLACEMENT,
        CAMP_YELLOW_PLACEMENT,
    };

    constexpr float HOSPITAL_SIZE = 100;
    const Placement HOSPITAL_RED_PLACEMENT = {{-375,-100},180, state::Color::Red};
    const Placement HOSPITAL_BLUE_PLACEMENT = {{375,-100},180, state::Color::Blue};
    const Placement HOSPITAL_GREEN_PLACEMENT = {{-375,100},0, state::Color::Green};
    const Placement HOSPITAL_YELLOW_PLACEMENT = {{375,100},0, state::Color::Yellow};
    const inline std::array ALL_HOSPITAL_PLACEMENT = {
        HOSPITAL_RED_PLACEMENT,
        HOSPITAL_BLUE_PLACEMENT,
        HOSPITAL_GREEN_PLACEMENT,
        HOSPITAL_YELLOW_PLACEMENT,
    };

    constexpr float CEMETERY_SIZE = 100;
    const Placement CEMETERY_RED_PLACEMENT = {{-120,-350},90, state::Color::Red};
    const Placement CEMETERY_BLUE_PLACEMENT = {{120,-350},-90, state::Color::Blue};
    const Placement CEMETERY_GREEN_PLACEMENT = {{-120,350},90, state::Color::Green};
    const Placement CEMETERY_YELLOW_PLACEMENT = {{120,350},-90, state::Color::Yellow};
    const inline std::array ALL_CEMETERY_PLACEMENT = {
        CEMETERY_RED_PLACEMENT,
        CEMETERY_BLUE_PLACEMENT,
        CEMETERY_GREEN_PLACEMENT,
        CEMETERY_YELLOW_PLACEMENT
    };
}
