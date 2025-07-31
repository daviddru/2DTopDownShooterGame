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

void Zombie::updateHitbox() {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float scale = 0.25f;
    float newWidth = bounds.width * scale;
    float newHeight = bounds.height * scale;
    float offsetX = (bounds.width - newWidth) / 2.f;
    float offsetY = (bounds.height - newHeight) / 2.f;
    hitbox = sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, newWidth, newHeight);
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

    updateHitbox();
}

void Zombie::draw(sf::RenderWindow& window) const {
    drawHealth(window);
    window.draw(sprite);
}

sf::Vector2f Zombie::getPosition() const {
    return sprite.getPosition();
}

float Zombie::getRadius() const {
    return radius;
}

sf::FloatRect Zombie::getBounds() const {
    return sprite.getGlobalBounds();
}

const sf::FloatRect& Zombie::getHitbox() const {
    return hitbox;
}

void Zombie::takeDamage(float damage) {
    health -= damage;
}

bool Zombie::isDead() const {
    return health <= 0;
}

float Zombie::getHealth() const {
    return health;
}

void Zombie::drawHealth(sf::RenderWindow& window) const {
    // Health bar background
    sf::RectangleShape back(sf::Vector2f(40, 5));
    back.setFillColor(sf::Color(50, 50, 50));
    back.setPosition(sprite.getPosition().x - 20, sprite.getPosition().y - 50);

    // Health bar foreground
    sf::RectangleShape bar(sf::Vector2f(40 * (health / 100.f), 5));
    bar.setFillColor(sf::Color::Red);
    bar.setPosition(sprite.getPosition().x - 20, sprite.getPosition().y - 50);

    window.draw(back);
    window.draw(bar);
}
