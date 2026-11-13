#include "render/StateRender.h"
using namespace render;

StateRender::StateRender (sf::RenderWindow& window, state::GameState& GameState) : window(window), currentState(GameState) {
    layers = {};
}

StateRender::~StateRender () = default;

void StateRender::render() {
    for (Layer& layer : layers) {
        layer.render(window);
    }
}
