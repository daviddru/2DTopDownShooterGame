//
// Created by david on 7/31/2025.
//

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"
#include <vector>

class ParticleSystem {
private:
    std::vector<Particle> particles;

public:
    void spawn(sf::Vector2f position, int count);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};



#endif //PARTICLESYSTEM_H
