#include "State/GameState.h"
#include "State/Board.h"

#include <memory>
const int NB_PLAYERS = 4;
using namespace State;

GameState::GameState() :
    turn(0),
    players(),
    current_Player_index(0),
    board(Board()),
    possible_Moves(),
    dice_Draw(),
    stone(Stone(Position(0,0))),
    dragon(Dragon(Position(0,0)))  {
        players.reserve(NB_PLAYERS);
        add_player(Color::Red, Position(0,0),Position(0,1));
        add_player(Color::Blue, Position(1,0),Position(1,1));
        add_player(Color::Green, Position(2,0),Position(2,1));
        add_player(Color::Yellow, Position(3,0),Position(3,1));
    }

int GameState::get_turn() {
    return turn;
}

Board& GameState::get_board() {
    return board;
}

Player& GameState::get_current_player() {
    return players.at(current_Player_index);
}

std::vector<Action> GameState::get_possible_actions() {
    return possible_Moves;
}

std::vector<Player> GameState::get_players() {
    return players;
}

Stone GameState::get_stone() {
    return stone;
}

Dragon GameState::get_dragon() {
    return dragon;
}


void GameState::add_player(Color color, Position warrior_position, Position sorcerer_position) {
    players.emplace_back(color, warrior_position, sorcerer_position);
    players.back().get_warrior().set_place(Place::Camp);
    players.back().get_sorcerer().set_place(Place::Camp);
}