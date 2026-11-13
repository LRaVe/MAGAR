#include <iostream>
using namespace std;

#include "state/ClassicTile.h"

using namespace state;


ClassicTile::ClassicTile(Position pos) : Tile(pos) {

}

ClassicTile::~ClassicTile() {}

void ClassicTile::effect() {
    cout << "Classic tile effect" << endl;
}
