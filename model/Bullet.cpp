//
// Created by david on 7/28/2025.
//

#include "Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, float speed, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.03, 0.03));
    sprite.setPosition(position);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f + 90.f;
    sprite.setRotation(angle);

    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = (len != 0) ? direction / len * speed : sf::Vector2f(0.f, 0.f);
}

void Bullet::update(float deltaTime) {
    sprite.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = sprite.getPosition();
    return pos.x < 0 || pos.y < 0 || pos.x > window.getSize().x || pos.y > window.getSize().y;
}