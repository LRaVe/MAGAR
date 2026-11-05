#include "State/Board.h"

#include <memory>
#include <iostream>
using namespace std;

#include "State/ClassicTile.h"
#include "State/NestTile.h"
#include "State/StarTile.h"
#include "State/CenterTile.h"

using namespace State;

constexpr int BOARD_RADIUS = 5;
constexpr int BOARD_DIAMETER = 11;
constexpr int NEST_RADIUS = 2;

Board::Board() {
    board.resize(BOARD_DIAMETER);
    for (int i = 0; i < BOARD_DIAMETER; i++) {
        board[i].resize(BOARD_DIAMETER);
    }

    // Classic Tile
    for (int q = -BOARD_RADIUS; q <= BOARD_RADIUS; q++) {
        int r1 = max(-BOARD_RADIUS, -q - BOARD_RADIUS);
        int r2 = min( BOARD_RADIUS, -q + BOARD_RADIUS);
        for (int r = r1; r <= r2; r++) {
            Position position = Position(q,r);
            set_tile_at(position, make_unique<ClassicTile>(position));
        }
    }

    // Nest Tile
    for (int q = -NEST_RADIUS; q <= NEST_RADIUS; q++) {
        int r1 = max(-NEST_RADIUS, -q - NEST_RADIUS);
        int r2 = min( NEST_RADIUS, -q + NEST_RADIUS);
        for (int r = r1; r <= r2; r++) {
            Position position = Position(q,r);
            set_tile_at(position, make_unique<NestTile>(position));
        }
    }

    // Star Tile
    vector<Position> start_tile_list = {
        Position(2,-4),
        Position(-1,-3),Position(4,-3),
        Position(-4,0),Position(4,0),
        Position(-4,3),Position(1,3),
        Position(-2,4)
    };
    for (const Position& pos : start_tile_list){
        set_tile_at(pos, make_unique<StarTile>(pos));
    }

    // Center Tile
    Position position = Position(0,0);
    set_tile_at(position, make_unique<CenterTile>(position));
}

void Board::set_tile_at(const Position& pos, unique_ptr<Tile> tile) {
    board[pos.r+5][pos.q+5] = std::move(tile);
}

unique_ptr<Tile> Board::get_tile_from(const Position& pos) {
    return std::move(board[pos.r-5][pos.q-5]);
}

vector<Position> start_tile_list(){
    return {
        Position(2,-4),
        Position(-1,-3),Position(4,-3),
        Position(-4,0),Position(4,0),
        Position(-4,3),Position(1,3),
        Position(-2,4)
    };
}

vector<Position> center_tile_list() {
    return {Position(0,0)};
}

vector<Position> get_circle_tile_list(int radius)
{
    vector<Position> result = {};
    for (int q = -radius; q <= radius; q++) {
        int r1 = max(-radius, -q - radius);
        int r2 = min( radius, -q + radius);
        for (int r = r1; r <= r2; r++) {
            Position position = Position(q,r);
            result.push_back(position);
        }
    }
    return result;
}