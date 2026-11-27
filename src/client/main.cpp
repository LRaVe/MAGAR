#include <SFML/Graphics.hpp>
#include "GameEngine/Engine.h"
#include <state.h>
#include "client/ClientInput.h"
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

    game_state.get_dragon().set_position(Position(2,-2));

    GameEngine::Engine engine(game_state);
    engine.start_turn();

    // Render State
    StateRender state_render = StateRender(window, game_state);
    client::ClientInput client_input(window, engine);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            } else {
                client_input.handle_event(event);
            }
        }
        window.clear(sf::Color::White);
        state_render.render();
        client_input.render();
        window.display();
    }
    return 0;
}
