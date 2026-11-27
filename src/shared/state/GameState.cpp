#include "state/GameState.h"
#include "state/Board.h"

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
    dragon(Dragon(Position(0,0))){
    add_player(Color::Red, Position(0,0), Position(0,0));
    add_player(Color::Blue, Position(0,0), Position(0,0));
    add_player(Color::Green, Position(0,0), Position(0,0));
    add_player(Color::Yellow, Position(0,0), Position(0,0));
}
GameState::~GameState() = default;

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
}

bool GameState::stone_is_on() {
    Position stone_pos = stone.get_position();

    bool stone_on_player = false;

    Position dragon_pos = dragon.get_position();
    stone_on_player = ((dragon_pos.q == stone_pos.q && dragon_pos.r == stone_pos.r)) || stone_on_player;

    for (auto& player : players) {
        Position w_pos = player.get_warrior().get_position();
        Position s_pos = player.get_sorcerer().get_position();

        bool on_warrior  = player.get_warrior().get_place() == state::Arena && (w_pos.q == stone_pos.q && w_pos.r == stone_pos.r);
        bool on_sorcerer = player.get_sorcerer().get_place() == state::Arena && (s_pos.q == stone_pos.q && s_pos.r == stone_pos.r);

        if (on_warrior || on_sorcerer) {
            stone_on_player = true;
            break;
        }
    }
    return stone_on_player;
}

void GameState::set_draw(const std::vector<Dice>& dice) {
    dice_Draw.set_draw(dice);
}