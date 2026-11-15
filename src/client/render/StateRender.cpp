#include "render/StateRender.h"

#include "DiceLayer.h"
#include "TurnLayer.h"
using namespace render;
#include <state/GameState.h>

StateRender::StateRender (sf::RenderWindow& window, state::GameState& GameState) : window(window), currentState(GameState) {
    layers.push_back(std::make_shared<TurnLayer>(currentState.get_turn(),currentState.get_current_player().getColor()));
    layers.push_back(std::make_shared<DiceLayer>(currentState.get_draw_dice()));
}

StateRender::~StateRender () = default;

void StateRender::setCurrentState(state::GameState& newState) {
    currentState = newState;
}

void StateRender::render() {
    for (const std::shared_ptr<Layer>& layer : layers){
        layer->render(window);
    }
}
