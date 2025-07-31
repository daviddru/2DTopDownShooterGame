//
// Created by david on 7/29/2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Zombie {
private:
    sf::Sprite sprite;
    float speed = 100.f;
    float radius = 30.f;
    sf::FloatRect hitbox;

public:
    Zombie(sf::Vector2f position, const sf::Texture& texture);

    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void updateHitbox();
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    float getRadius() const;
    sf::FloatRect getBounds() const;
    const sf::FloatRect& getHitbox() const;
    void move(const sf::Vector2f& offset, float deltaTime);
};

#endif //ENEMY_H
