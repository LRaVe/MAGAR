#include "State/Board.h"

#include  <iostream>
using namespace std;

using namespace State;

#define N 5

Board::Board() {
    for (int q = -N; q <= N; q++) {
        int r1 = max(-N, -q - N);
        int r2 = min( N, -q + N);
        for (int r = r1; r <= r2; r++) {
        }
    }
}