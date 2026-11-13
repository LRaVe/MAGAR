#include <iostream>
using namespace std;

#include "state/StarTile.h"
#include "state/Position.h"
#include "state/Tile.h"

using namespace state;

state::StarTile::StarTile (Position pos) : Tile (pos){

}

StarTile::~StarTile() {}

void StarTile::effect() {
    cout << "Star tile effect" << endl;
}
