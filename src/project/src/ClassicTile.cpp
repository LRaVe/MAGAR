#include <iostream>
using namespace std;

#include "../include/State/ClassicTile.h"

using namespace State;


ClassicTile::ClassicTile(Position pos) : Tile(pos) {

}

void ClassicTile::effect() {
    cout << "Classic tile effect" << endl;
}
