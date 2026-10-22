#include <iostream>
using namespace std;

#include "State/NestTile.h"

using namespace State;


NestTile::NestTile(Position pos) :  Tile(pos) {

}

void NestTile::effect() {
    cout << "Nest tile effect" << endl;
}
