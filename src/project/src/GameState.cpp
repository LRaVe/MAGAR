#include "State/GameState.h"
#include "State/Board.h"
using namespace State;

GameState::GameState() :
    turn(0),
    players(),
    current_Player(players[turn%players.size()]),
    board(Board::get_instance()),
    possible_Moves(),
    dice_Draw() {
}

int GameState::get_turn() {
    return turn;
}

Board GameState::get_board() {
    return board;
}

Player GameState::get_current_player(){
    return current_Player;
}

std::vector<Action> GameState::get_possible_actions() {
    return possible_Moves;
}

std::vector<Player> GameState::get_players() {
    return players;
}

