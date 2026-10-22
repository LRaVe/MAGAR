#include "State/GameState.h"
#include "State/Board.h"
using namespace State;

GameState::GameState() :
    turn(0),
    players(),
    current_Player(players[turn%players.size()]),
    board(Board()),
    possible_Moves(),
    dice_Draw(),
    stone(Stone(Position(0,0))),
    dragon(Dragon(Position(0,0)))  {
        for (int i=0;i<4;i++) {
            players.emplace_back(Player(static_cast<Color>(i)));
        }
        current_Player = players[turn%players.size()];
}

int GameState::get_turn() {
    return turn;
}

Board GameState::get_board() {
    return std::move(board);
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

Stone GameState::get_stone() {
    return stone;
}

Dragon GameState::get_dragon() {
    return dragon;
}
