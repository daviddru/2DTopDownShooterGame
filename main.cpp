#include <SFML/Graphics.hpp>
#include "model/Player.h"
#include "model/Bullet.h"
#include "model/SoundManager.h"
#include "model/Zombie.h"
#include <iostream>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Twin Stick Shooter");
    window.setFramerateLimit(60);

    Player player;
    sf::Clock clock;

    std::vector<Bullet> bullets;
    sf::Clock shootClock;

    std::vector<Zombie> enemies;
    sf::Clock enemySpawnClock;

    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("../model/assets/bullet.png")) {
        std::cerr << "Failed to load bullet texture\n";
        return 1;
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../model/assets/enemy.png")) {
        std::cerr << "Failed to load enemy texture\n";
        return 1;
    }

    SoundManager::getInstance().loadSound("shoot", "../model/assets/sounds/shoot.wav");

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update player
        player.update(window, deltaTime);

        // Update shooting
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (shootClock.getElapsedTime().asSeconds() > 0.4f) { // rate limit
                sf::Vector2f playerPos = player.getPosition();
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f direction = mousePos - playerPos;

                float muzzleLength = 186.f/2;
                sf::Vector2f bulletSpawn = playerPos + direction * (muzzleLength / std::sqrt(direction.x * direction.x + direction.y * direction.y));

                bullets.emplace_back(bulletSpawn, direction, 800.f, bulletTexture);
                SoundManager::getInstance().playSound("shoot");
                shootClock.restart();
            }
        }

        // Spawn enemies
        if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f) {
            sf::Vector2f spawnPos(rand() % 1920, rand() % 1080);
            enemies.emplace_back(spawnPos, enemyTexture);
            enemySpawnClock.restart();
        }

        // Delete out of bound bullets
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
    [&](const Bullet& b) { return b.isOffScreen(window); }),
    bullets.end());

        window.clear(sf::Color::Black);

        // Update and draw bullets
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
            bullet.draw(window);
        }

        // Update and draw enemies
        for (auto& enemy : enemies) {
            enemy.update(player.getCenter(), deltaTime);
            enemy.draw(window);
        }

        // Draw elements
        player.draw(window);

        window.display();

        SoundManager::getInstance().cleanup();
    }


    return 0;
}