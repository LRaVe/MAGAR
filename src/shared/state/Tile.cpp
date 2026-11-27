#include "state/Tile.h"
#include "state/Position.h"

using namespace state;

Tile::Tile (Position pos) : position (pos) {
    
}

Tile::~Tile() = default;

void Tile::effect() {}

bool Tile::is_star_tile() const
{
    return false;
}

bool Tile::is_nested_tile() const
{
    return false;
}

Position Tile::get_position() const {
    return position;
}
