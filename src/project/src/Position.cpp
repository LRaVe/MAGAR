#include "State/Position.h"

using namespace State;

Position::Position(int q, int r) : q(q), r(r) {

}

int Position::s(){
    return - q -r;
}
