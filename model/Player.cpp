//
// Created by david on 7/27/2025.
//

#include "Player.h"

#include <cmath>
#include <iostream>

Player::Player() {
    if (!texture.loadFromFile("../model/assets/player.png")) {
        // Handle error: e.g., print or throw
        std::cerr << "Failed to load player texture\n";
    }

    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.5, 0.5));
    sprite.setOrigin(150.f, 100.f);  // Center origin for rotation
    sprite.setPosition(640.f, 360.f);

    speed = 300.f;
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1;

    if (movement.x != 0.f && movement.y != 0.f) {
        float len = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= len;
    }

    sprite.move(movement * speed * deltaTime);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::update(sf::RenderWindow& window, float deltaTime) {
    handleInput(deltaTime);

    sf::Vector2f playerPos = sprite.getPosition();

    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    // Direction from player to mouse
    sf::Vector2f direction = mouseWorldPos - playerPos;

    // Angle of the direction
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;

    // Set rotation (+90 if the shape initially faces up)
    sprite.setRotation(angle);
}


