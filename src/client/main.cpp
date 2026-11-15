#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>
// LCOV_EXCL_START
void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <state.h>
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

// int argc,char* argv[]
int main(){

    // Window
    // sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Magar : Le Dragon et la Pierre" );
    sf::RenderWindow window( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Magar : Le Dragon et la Pierre" );
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::FloatRect({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    view.setCenter({0.f, 0.f});
    window.setView(view);

    // GameState
    GameState game_state = GameState();

    // Render State
    StateRender state_render = StateRender(window, game_state);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        state_render.render();
        window.display();
    }
    return 0;
}

// LCOV_EXCL_END
