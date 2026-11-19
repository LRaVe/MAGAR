#include "state/Position.h"
#include <cstdlib>

using namespace state;

Position::Position(int q, int r) : q(q), r(r) {
    
}

Position::~Position() {}

int Position::s() const {
    return - q -r;
}

Position Position::subtract(const Position& other) const {
    return Position(q - other.q, r - other.r);
}

int Position::distance_to(const Position& other) const {
    const Position difference = subtract(other);
    return (std::abs(difference.q)
            + std::abs(difference.r)
            + std::abs(difference.s())) / 2;
}

bool Position::is_adjacent_to(const Position& other) const {
    return distance_to(other) == 1;
}

bool Position::is_in_radius(int radius) const {
    return distance_to(Position(0, 0)) <= radius;
}

Position Position::neighbor(int direction) const {
    static const int directions[6][2] = {
        {1, 0}, {1, -1}, {0, -1},
        {-1, 0}, {-1, 1}, {0, 1}
    };
    if (direction < 0 || direction >= 6) {
        return *this;
    }
    return Position(q + directions[direction][0],
                    r + directions[direction][1]);
}

std::vector<Position> Position::neighbors() const {
    std::vector<Position> result;
    result.reserve(6);
    for (int direction = 0; direction < 6; ++direction) {
        result.push_back(neighbor(direction));
    }
    return result;
}

std::vector<Position> Position::ring(int radius) const {
    std::vector<Position> result;
    if (radius == 0) {
        result.push_back(*this);
        return result;
    }
    if (radius < 0) {
        return result;
    }

    Position cursor = neighbor(4);
    for (int i = 1; i < radius; ++i) {
        cursor = cursor.neighbor(4);
    }
    for (int side = 0; side < 6; ++side) {
        for (int step = 0; step < radius; ++step) {
            result.push_back(cursor);
            cursor = cursor.neighbor(side);
        }
    }
    return result;
}
