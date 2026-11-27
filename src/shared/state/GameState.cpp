#include "state/GameState.h"
#include "state/Board.h"
#include "GameEngine/Action.h"

#include <algorithm>
#include <memory>
const int NB_PLAYERS = 4;
using namespace state;

GameState::GameState() :
    turn(0),
    players(),
    current_Player_index(0),
    board(Board()),
    dice_Draw(),
    stone(Stone(Position(0,0))),
    dragon(Dragon(Position(0,0))),
    attacked_pawns_this_turn(){
    add_player(Color::Red, Position(0,0), Position(0,0));
    add_player(Color::Blue, Position(0,0), Position(0,0));
    add_player(Color::Green, Position(0,0), Position(0,0));
    add_player(Color::Yellow, Position(0,0), Position(0,0));
}
GameState::~GameState() {}

int GameState::get_turn() {
    return turn;
}

Board& GameState::get_board() {
    return board;
}

Player& GameState::get_current_player() {
    return players.at(current_Player_index);
}


std::vector<Player>& GameState::get_players() {
    return players;
}

DrawDice& GameState::get_draw_dice() {
    return dice_Draw;
}

Stone& GameState::get_stone() {
    return stone;
}

Dragon& GameState::get_dragon() {
    return dragon;
}

bool GameState::has_attacked_this_turn(const PlayablePawn& pawn) const {
    return std::find(
        attacked_pawns_this_turn.begin(),
        attacked_pawns_this_turn.end(),
        &pawn) != attacked_pawns_this_turn.end();
}

void GameState::mark_attack_used(PlayablePawn& pawn) {
    if (!has_attacked_this_turn(pawn)) {
        attacked_pawns_this_turn.push_back(&pawn);
    }
}


void GameState::add_player(Color color, Position warrior_position, Position sorcerer_position) {
    players.emplace_back(color, warrior_position, sorcerer_position);
    players.back().get_warrior().set_place(Place::Camp);
    players.back().get_sorcerer().set_place(Place::Camp);
}

void GameState::next_turn() {
    if (players.empty()) {
        return;
    }
    current_Player_index =
        (current_Player_index + 1) % players.size();
    ++turn;
    attacked_pawns_this_turn.clear();
}