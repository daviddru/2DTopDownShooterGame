//
// Created by david on 7/31/2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;

public:
    Particle(sf::Vector2f position, sf::Vector2f velocity, float lifetime);

    bool isDead() const;
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};



#endif //PARTICLE_H
