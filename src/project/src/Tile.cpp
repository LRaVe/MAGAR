#include "State/Tile.h"
#include "State/Position.h"

using namespace State;

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