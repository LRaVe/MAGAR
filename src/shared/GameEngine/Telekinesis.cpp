#include "GameEngine/Telekinesis.h"
#include "state/GameState.h"
#include <algorithm>
#include <cmath>

namespace GameEngine {
using namespace state;

Telekinesis::Telekinesis(const Position& destination) : Spell(), destination(destination) {}

Telekinesis::~Telekinesis() = default;

int Telekinesis::get_nb_of_dice(GameState& state) {
    return state.stone_is_on() ? 3 : 1;
}

std::vector<Position> Telekinesis::ListOfMoves(GameState& state) const {
    Position stone_pos = state.get_stone().get_position();

    static const std::pair<int, int> hex_directions[6] = {
        {1,0},
        {1,-1},
        {0,-1},
        {-1,0},
        {-1,1},
        {0,1}
    };
    std::vector<Position> possible_moves;

    for (const auto& dir : hex_directions)
    {
        Position neighbor(stone_pos.q + dir.first, stone_pos.r + dir.second);

        const int distance_q = std::abs(neighbor.q);
        const int distance_r = std::abs(neighbor.r);
        const int distance_s = std::abs(neighbor.q + neighbor.r);
        const int distance_from_center =
            std::max(distance_q, std::max(distance_r, distance_s));

        if (distance_from_center <= 5)
        {
            possible_moves.push_back(neighbor);
        }
    }

    return possible_moves;
}

void Telekinesis::execute(GameState& state) const
{
        state.get_stone().set_position(this->destination);
}

}