//
// Created by david on 7/29/2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite sprite;
    float speed = 100.f;
    bool alive = true;

public:
    Enemy(sf::Vector2f position, const sf::Texture& texture);

    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isHit(const sf::FloatRect& bulletBounds) const;
    bool isAlive() const;
    sf::FloatRect getBounds() const;
};

#endif //ENEMY_H
