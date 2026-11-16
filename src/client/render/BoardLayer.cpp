#include  "render/BoardLayer.h"
using namespace render;

BoardLayer::BoardLayer(state::Board& board) : board(board) {

}

BoardLayer::~BoardLayer() = default;

void BoardLayer::render(sf::RenderWindow& window){
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Black);
    circle.setRadius(10);
    window.draw(circle);
}
