#include "state/Tile.h"
#include "state/Position.h"

using namespace state;

Tile::Tile (Position pos) : position (pos) {
    
}

Tile::~Tile() {}

void Tile::effect() {}

const Position& Tile::getPosition() const {
    return position;
}

void Tile::setPosition(const Position& new_position) {
    position = new_position;
}