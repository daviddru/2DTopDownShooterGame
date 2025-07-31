//
// Created by david on 7/31/2025.
//

#include "ParticleSystem.h"

#include <cmath>

void ParticleSystem::spawn(sf::Vector2f position, int count) {
    for (int i = 0; i < count; ++i) {
        float angle = static_cast<float>(rand() % 360) * 3.14f / 180.f;
        float speed = 50.f + rand() % 100;
        sf::Vector2f velocity(std::cos(angle) * speed, std::sin(angle) * speed);
        particles.emplace_back(position, velocity, 0.5f);
    }
}

void ParticleSystem::update(float deltaTime) {
    for (int i = 0; i < particles.size(); ++i) {
        particles[i].update(deltaTime);
    }

    particles.erase(remove_if(particles.begin(), particles.end(),[](const Particle& p) {
        return p.isDead();
    }), particles.end());
}

void ParticleSystem::draw(sf::RenderWindow& window) {
    for (int i = 0; i < particles.size(); ++i) {
        particles[i].draw(window);
    }
}