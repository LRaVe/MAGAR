#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>
// LCOV_EXCL_START
void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include "../project/include/State.h"
#include "../project/include/render.h"

using namespace std;
using namespace State;
using namespace render;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

int main(int argc,char* argv[]){

    // Window
    sf::RenderWindow window( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Magar : Le Dragon et la Pierre" );
    window.setVerticalSyncEnabled(true);

    // GameState
    //GameState game_state = GameState();

    // Render State
    //StateRender state_render = StateRender(window, game_state);



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Cyan);
        window.display();
    }
    return 0;
}

// LCOV_EXCL_END
