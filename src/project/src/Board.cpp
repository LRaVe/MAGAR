#include "State/Board.h"

#include  <iostream>
using namespace std;

#include "State/ClassicTile.h"
#include "State/NestTile.h"
#include "State/StarTile.h"
#include "State/CenterTile.h"

using namespace State;

#define N 5

Board::Board() {
    board.resize(2*N+1);
    for (int i = 0; i < 2*N+1; i++) {
        board[i].resize(2*N+1);
    }

    // Classic Tile
    for (int q = -N; q <= N; q++) {
        int r1 = max(-N, -q - N);
        int r2 = min( N, -q + N);
        for (int r = r1; r <= r2; r++) {
            Position position = Position(q,r);
            set_tile_at(position, make_unique<ClassicTile>(position));
        }
    }

    // Nest Tile
    int N_nest = N - 3;
    for (int q = -N_nest; q <= N_nest; q++) {
        int r1 = max(-N_nest, -q - N_nest);
        int r2 = min( N_nest, -q + N_nest);
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
    for (Position pos : start_tile_list){
        set_tile_at(pos, make_unique<StarTile>(pos));

    }

    // Center Tile
    Position position = Position(0,0);
    set_tile_at(position, make_unique<CenterTile>(position));
}