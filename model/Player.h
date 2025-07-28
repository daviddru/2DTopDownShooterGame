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

public:
    Player();

    void handleInput(float deltaTime);
    void draw(sf::RenderWindow &window);
    void update(sf::RenderWindow& window, float deltaTime);


    sf::Vector2f getPosition() const;
};



#endif //PLAYER_H
