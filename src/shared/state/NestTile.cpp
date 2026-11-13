#include <iostream>
using namespace std;

#include "state/NestTile.h"

using namespace state;


NestTile::NestTile(Position pos) :  Tile(pos) {

}

NestTile::~NestTile() = default;

void NestTile::effect() {
    cout << "Nest tile effect" << endl;
}
