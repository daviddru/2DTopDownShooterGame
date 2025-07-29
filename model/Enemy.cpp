//
// Created by david on 7/29/2025.
//

#include "Enemy.h"
#include <cmath>

Enemy::Enemy(sf::Vector2f position, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.4f, 0.4f);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}


void Enemy::update(const sf::Vector2f& playerPosition, float deltaTime) {
    sf::Vector2f dir = playerPosition - sprite.getPosition();
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;

    sprite.move(dir * speed * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

