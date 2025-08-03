//
// Created by david on 7/27/2025.
//

#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>


class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float speed;
    int maxHealth = 100.f;
    int currentHealth = 100.f;

public:
    Player();

    void handleInput(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);
    void update(sf::RenderWindow& window, float deltaTime);
    void takeDamage(int damage);
    void reset();


    sf::Vector2f getPosition() const;
    sf::Vector2f getCenter() const;
    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;
};



#endif //PLAYER_H
