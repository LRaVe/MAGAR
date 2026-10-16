#include "../include/State/Board.h"

#include  <iostream>
using namespace std;

using namespace State;

#define N 5

Board::Board() {
    for (int q = -N; q <= N; q++) {
        int r1 = max(-N, -q - N);
        int r2 = min( N, -q + N);
        for (int r = r1; r <= r2; r++) {
            board.emplace_back(Position(q,r));
        }
    }
}

std::vector<Tile> Board::get_board() {
    return board;
}
