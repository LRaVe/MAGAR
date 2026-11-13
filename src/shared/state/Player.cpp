#include "state/Player.h"
using namespace state;

// constructor's attributes are: color, warrior, sorcerer
Player::Player(Color color, Position warrior_position, Position sorcerer_position) : 
    color(color),
    warrior(color, warrior_position),
    sorcerer(color, sorcerer_position) {}

Player::~Player() {}

Warrior& Player::get_warrior() {
    return warrior;
}

Sorcerer& Player::get_sorcerer() {
    return sorcerer;
}