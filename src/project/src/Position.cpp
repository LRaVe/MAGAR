#include "State/Position.h"

using namespace State;

Position::Position(int q, int r) : q(q), r(r) {

}

Position::~Position() {}

int Position::s() const {
    return - q -r;
}
