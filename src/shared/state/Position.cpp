#include "state/Position.h"

using namespace state;

Position::Position(int q, int r) : q(q), r(r) {
    
}

Position::~Position() {}

int Position::s() const {
    return - q -r;
}
