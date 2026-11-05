#include "State/Player.h"
using namespace State;
#include "State/Player.h"
using namespace State;

// constructor's attributes are: color, warrior, sorcerer
Player::Player(Color color, Position warrior_position, Position sorcerer_position) : 
    color(color),
    warrior(color, warrior_position),
    sorcerer(color, sorcerer_position) {}