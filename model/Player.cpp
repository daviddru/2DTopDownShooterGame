//
// Created by david on 7/27/2025.
//

#include "Player.h"

#include <cmath>

Player::Player() {
    shape.setRadius(25.f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(640.f, 360.f);

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

    shape.move(movement * speed * deltaTime);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

