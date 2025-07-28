#include <SFML/Graphics.hpp>
#include "model/Player.h"
#include "model/Bullet.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Twin Stick Shooter");
    window.setFramerateLimit(60);

    Player player;
    sf::Clock clock;

    std::vector<Bullet> bullets;
    sf::Clock shootClock;

    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("../model/assets/bullet.png")) {
        std::cerr << "Failed to load bullet texture\n";
        return 1;
    }

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        player.update(window, deltaTime);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (shootClock.getElapsedTime().asSeconds() > 0.15f) { // rate limit
                sf::Vector2f playerPos = player.getPosition();
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f direction = mousePos - playerPos;

                bullets.emplace_back(playerPos, direction, 800.f, bulletTexture);
                shootClock.restart();
            }
        }
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
    [&](const Bullet& b) { return b.isOffScreen(window); }),
    bullets.end());

        window.clear(sf::Color::Black);
        player.draw(window);
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }
        window.display();
    }


    return 0;
}