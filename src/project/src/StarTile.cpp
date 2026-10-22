#include <iostream>
using namespace std;

#include "State/StarTile.h"
#include "State/Position.h"
#include "State/Tile.h"

using namespace State;

State::StarTile::StarTile (Position pos) : Tile (pos){

}


void StarTile::effect() {
    cout << "Star tile effect" << endl;
}
