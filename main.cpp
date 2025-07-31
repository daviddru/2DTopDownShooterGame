#include <SFML/Graphics.hpp>
#include "model/Player.h"
#include "model/Bullet.h"
#include "model/SoundManager.h"
#include "model/Zombie.h"
#include <iostream>
#include <cmath>


void applyZombieSeparation(std::vector<Zombie>& zombies, float deltaTime) {
    float separationRadius = 50.f;
    float pushStrength = 100.f;

    for (size_t i = 0; i < zombies.size(); ++i) {
        for (size_t j = i + 1; j < zombies.size(); ++j) {
            sf::Vector2f posA = zombies[i].getPosition();
            sf::Vector2f posB = zombies[j].getPosition();

            sf::Vector2f delta = posA - posB;
            float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

            if (distance < separationRadius && distance > 0.01f) {
                sf::Vector2f pushDir = delta / distance;
                float overlap = separationRadius - distance;
                sf::Vector2f push = pushDir * overlap * pushStrength;

                zombies[i].move(push * 0.5f, deltaTime);
                zombies[j].move(-push * 0.5f, deltaTime);
            }
        }
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Twin Stick Shooter");
    window.setFramerateLimit(60);

    Player player;
    sf::Clock clock;

    std::vector<Bullet> bullets;
    sf::Clock shootClock;

    std::vector<Zombie> enemies;
    int enemiesCount = 0;
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

        // Spawn enemies
        if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f) {
            sf::Vector2f spawnPos(rand() % 1920, rand() % 1080);
            if (enemiesCount < 20) {
                enemies.emplace_back(spawnPos, enemyTexture);
                enemiesCount++;
            }
            enemySpawnClock.restart();
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

        // Update bullets
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
        }

        // Update enemies
        for (auto& enemy : enemies) {
            applyZombieSeparation(enemies, deltaTime);
            enemy.update(player.getCenter(), deltaTime);
        }

        // Check for collisions
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
            bool bulletRemoved = false;
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
                if (bulletIt->getHitbox().intersects(enemyIt->getHitbox())) {
                    // Remove bullet
                    bulletIt = bullets.erase(bulletIt);
                    bulletRemoved = true;

                    // Remove enemy (or call enemy.takeDamage() if you want health)
                    enemyIt = enemies.erase(enemyIt);

                    break; // bullet is gone, stop checking enemies for this bullet
                } else {
                    ++enemyIt;
                }
            }
            if (!bulletRemoved) {
                ++bulletIt;
            }
        }

        // Delete out of bound bullets
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
    [&](const Bullet& b) { return b.isOffScreen(window); }),
    bullets.end());

        window.clear(sf::Color::Black);

        // Draw bullets
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }

        // Draw enemies
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }

        // Draw elements
        player.draw(window);

        window.display();

        SoundManager::getInstance().cleanup();
    }


    return 0;
}