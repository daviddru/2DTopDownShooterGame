//
// Created by david on 7/28/2025.
//

#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>


class Bullet {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    sf::FloatRect hitbox;

public:
    Bullet(sf::Vector2f position, sf::Vector2f direction, float speed, const sf::Texture& texture);
    void updateHitbox();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(const sf::RenderWindow& window) const;
    const sf::FloatRect& getHitbox() const;
    sf::FloatRect getBounds() const;
};



#endif //BULLET_H
