#include "render/StateRender.h"
using namespace render;

StateRender::StateRender (sf::RenderWindow& window, State::GameState GameState) : window(window), currentState(GameState)
{
}
