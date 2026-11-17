#include "state/Tile.h"
#include "state/Position.h"

using namespace state;

Tile::Tile (Position pos) : position (pos) {
    
}

Tile::~Tile() = default;

void Tile::effect() {}

Position Tile::get_position() const {
    return position;
}
