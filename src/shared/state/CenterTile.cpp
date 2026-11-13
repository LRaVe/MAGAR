#include <iostream>
using namespace std;

#include "state/CenterTile.h"

using namespace state;


CenterTile::CenterTile(Position pos) : Tile(pos) {

}

CenterTile::~CenterTile() {}

void CenterTile::effect() {
    cout << "Center tile effect" << endl;
}
