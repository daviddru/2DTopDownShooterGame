//
// Created by david on 7/31/2025.
//

#include "Particle.h"

Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, float life)
    : velocity(vel), lifetime(life) {
    shape.setRadius(3.f);
    shape.setFillColor(sf::Color(150, 0, 0));
    shape.setPosition(pos);
    shape.setOrigin(1.f, 1.f);
}

bool Particle::isDead() const {
    return lifetime <= 0.f;
}

void Particle::update(float deltaTime) {
    shape.move(velocity * deltaTime);
    lifetime -= deltaTime;

    // Fade out
    sf::Color color = shape.getFillColor();
    if (color.a > 0)
        color.a = static_cast<sf::Uint8>(std::max(0.f, color.a - 255.f * deltaTime));
    shape.setFillColor(color);
}

void Particle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}