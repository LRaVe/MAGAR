#include <iostream>
using namespace std;

#include "State/CenterTile.h"

using namespace State;


CenterTile::CenterTile(Position pos) : Tile(pos) {

}

void CenterTile::effect() {
    cout << "Center tile effect" << endl;
}
