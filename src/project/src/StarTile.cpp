#include <iostream>
using namespace std;

#include "../include/State/StarTile.h"

using namespace State;


StarTile::StarTile(Position pos) :  Tile(pos) {

}

void StarTile::effect() {
    cout << "Star tile effect" << endl;
}
