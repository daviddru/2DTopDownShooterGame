#include <SFML/Graphics.hpp>
#include "model/Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Twin Stick Shooter");
    window.setFramerateLimit(60);

    Player player;
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handleInput(deltaTime);
        // player.update(deltaTime);


        window.clear(sf::Color::Black);
        player.draw(window);
        window.display();
    }

    return 0;
}