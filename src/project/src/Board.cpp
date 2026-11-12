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

vector<Position> start_tile_list();
vector<Position> center_tile_list();
vector<Position> get_circle_tile_list(int radius);
vector<Position> get_circle_tile_list(int radius, int center);

Board::Board() {
    board.resize(BOARD_DIAMETER);
    for (int i = 0; i < BOARD_DIAMETER; i++) {
        board[i].resize(BOARD_DIAMETER);
    }

    // Classic Tile
    set_tiles_from_list<ClassicTile>(get_circle_tile_list(BOARD_RADIUS));

    // Nest Tile
    set_tiles_from_list<ClassicTile>(get_circle_tile_list(NEST_RADIUS));

    // Star Tile
    set_tiles_from_list<StarTile>(start_tile_list());

    // Center Tile
    vector<Position> center_tiles = center_tile_list();
    for (Position& pos : center_tiles) {
        set_tile_at(pos, make_unique<CenterTile>(pos));
    }
}

void Board::set_tile_at(const Position& pos, unique_ptr<Tile> tile) {
    board[pos.r+BOARD_RADIUS][pos.q+BOARD_RADIUS] = std::move(tile);
}

unique_ptr<Tile> Board::get_tile_from(const Position& pos) {
    return std::move(board[pos.r+BOARD_RADIUS][pos.q+BOARD_RADIUS]);
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

vector<Position> get_circle_tile_list(int radius) {
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

vector<Position> get_circle_tile_list(int radius, int center) {
    vector<Position> result = get_circle_tile_list(radius);
    for (Position& pos : result) {
        pos.q += center;
        pos.r += center;
    }
    return result;
}

template <typename TileType>
void Board::set_tiles_from_list(const vector<Position>& tile_list) {
    for (const Position& pos : tile_list) {
        set_tile_at(pos, make_unique<TileType>(pos));
    }
}