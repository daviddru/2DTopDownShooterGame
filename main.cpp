#include <SFML/Graphics.hpp>
#include "model/Player.h"
#include "model/Bullet.h"
#include "model/SoundManager.h"
#include "model/Zombie.h"
#include "model/ParticleSystem.h"
#include "model/GUI.h"
#include <iostream>
#include <cmath>

enum class GameState {
    Playing,
    GameOver
};

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

void toggleFullscreen(sf::RenderWindow& window, bool& isFullscreen) {
    if (isFullscreen) {
        window.create(sf::VideoMode(1920, 1080), "Twin Stick Shooter", sf::Style::Default); // windowed mode
    } else {
        window.create(sf::VideoMode::getDesktopMode(), "Twin Stick Shooter", sf::Style::Fullscreen); // fullscreen
    }

    isFullscreen = !isFullscreen;
    window.setFramerateLimit(60);
}


int main() {
    bool isFullscreen = true;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Twin Stick Shooter", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    GameState gameState = GameState::Playing;

    GUI gui;

    Player player;
    sf::Clock clock;

    std::vector<Bullet> bullets;
    sf::Clock shootClock;

    std::vector<Zombie> enemies;
    int enemiesCount = 0;
    sf::Clock enemySpawnClock;

    ParticleSystem bloodParticles;

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
    SoundManager::getInstance().loadSound("reload", "../model/assets/sounds/reload.wav");

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
                toggleFullscreen(window, isFullscreen);

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
                player.toggleSprint();
        }

        if (gameState == GameState::Playing) {
            // Spawn enemies
            if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f) {
                sf::Vector2f spawnPos(rand() % 1920, rand() % 1080);
                if (enemiesCount < 20) {
                    enemies.emplace_back(spawnPos, enemyTexture);
                    enemiesCount++;
                }
                enemySpawnClock.restart();
            }

            // Update GUI
            gui.updateHealth(player.getHealth(), player.getMaxHealth());
            gui.updateAmmo(player.getCurrentBullets(), player.getMaxBullets(), player.isReloading());
            gui.updateStamina(player.getStamina(), player.getMaxStamina());

            // Update player
            player.update(window, deltaTime);
            if (!player.isAlive()) {
                gameState = GameState::GameOver;
            }

            // Reload button
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                if (!player.isReloading())
                    SoundManager::getInstance().playSound("reload");
                player.reload();
            }

            // Update shooting
            if (window.hasFocus() && player.canShoot() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (shootClock.getElapsedTime().asSeconds() > 0.4f) { // rate limit
                    sf::Vector2f playerPos = player.getPosition();
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::Vector2f direction = mousePos - playerPos;

                    float muzzleLength = 186.f/2;
                    sf::Vector2f bulletSpawn = playerPos + direction * (muzzleLength / std::sqrt(direction.x * direction.x + direction.y * direction.y));

                    player.shoot();
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

                // Damage logic
                sf::Vector2f enemyPos = enemy.getPosition();
                sf::Vector2f playerPos = player.getCenter();
                float dist = std::hypot(enemyPos.x - playerPos.x, enemyPos.y - playerPos.y);

                if (dist < 70.f) {
                    static sf::Clock damageClock;
                    if (damageClock.getElapsedTime().asSeconds() > 0.7f) {
                        player.takeDamage(20);
                        damageClock.restart();
                    }
                }

                enemy.update(player.getCenter(), deltaTime);
            }

            // Update particles
            bloodParticles.update(deltaTime);

            // Check for collisions
            for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
                bool bulletRemoved = false;
                for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
                    if (bulletIt->getHitbox().intersects(enemyIt->getHitbox())) {
                        enemyIt->takeDamage(34.f);
                        bloodParticles.spawn(enemyIt->getPosition(), 15);

                        // Remove bullet
                        bulletIt = bullets.erase(bulletIt);
                        bulletRemoved = true;

                        if (enemyIt->isDead()) {
                            enemyIt = enemies.erase(enemyIt); // remove dead zombie
                            enemiesCount--;
                        } else {
                            ++enemyIt;
                        }
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

            // Draw particles
            bloodParticles.draw(window);

            // Draw elements
            player.draw(window);

            // Draw GUI
            gui.draw(window);

            window.display();
        }
        else if (gameState == GameState::GameOver) {
            gui.deathScreen(window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                player.reset();
                enemies.clear();
                bullets.clear();
                gameState = GameState::Playing;
            }
        }
    }

    return 0;
}