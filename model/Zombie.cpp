//
// Created by david on 7/29/2025.
//

#include "Zombie.h"
#include <cmath>

Zombie::Zombie(sf::Vector2f position, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.4f, 0.4f);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Zombie::move(const sf::Vector2f& offset, float deltaTime) {
    sprite.move(offset * deltaTime);
}

void Zombie::update(const sf::Vector2f& playerPosition, float deltaTime) {
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f toPlayer = playerPosition - pos;

    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    float playerRadius = 30.f;
    float stopDistance = radius + playerRadius;

    if (dist > stopDistance) {
        sf::Vector2f dir = toPlayer / dist;
        sprite.move(dir * speed * deltaTime);
        float angle = std::atan2(dir.y, dir.x) * 180 / 3.14159f;
        sprite.setRotation(angle);
    }
}

void Zombie::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Vector2f Zombie::getPosition() const {
    return sprite.getPosition();
}

float Zombie::getRadius() const {
    return radius;
}