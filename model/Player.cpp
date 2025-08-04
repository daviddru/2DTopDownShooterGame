//
// Created by david on 7/27/2025.
//

#include "Player.h"

#include <cmath>
#include <iostream>

Player::Player() {
    if (!texture.loadFromFile("../model/assets/player.png")) {
        // Handle error: e.g., print or throw
        std::cerr << "Failed to load player texture\n";
    }

    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.5, 0.5));
    sprite.setOrigin(95.f, 152.f);  // Center origin for rotation
    sprite.setPosition(640.f, 360.f);
}

void Player::handleInput(float deltaTime, const sf::RenderWindow& window) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1;

    if (movement.x != 0.f || movement.y != 0.f) {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        if (length != 0.f) {
            movement /= length;
        }

        if (isSprinting) {
            movement *= sprintSpeed * deltaTime;
        }
        else {
            movement *= speed * deltaTime;
        }

        sf::Vector2f newPos = sprite.getPosition() + movement;
        sf::FloatRect bounds = sprite.getGlobalBounds();
        float halfWidth = bounds.width / 2.f;
        float halfHeight = bounds.height / 2.f;

        float winWidth = static_cast<float>(window.getSize().x);
        float winHeight = static_cast<float>(window.getSize().y);

        // Clamp X movement
        if (newPos.x - halfWidth >= 0 && newPos.x + halfWidth <= winWidth) {
            sprite.move(movement.x, 0.f);
        }

        // Clamp Y movement
        if (newPos.y - halfHeight >= 0 && newPos.y + halfHeight <= winHeight) {
            sprite.move(0.f, movement.y);
        }
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::update(sf::RenderWindow& window, float deltaTime) {
    handleInput(deltaTime, window);

    updateReload(deltaTime);
    updateStamina(deltaTime);

    sf::Vector2f playerPos = sprite.getPosition();

    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    // Direction from player to mouse
    sf::Vector2f direction = mouseWorldPos - playerPos;

    // Angle of the direction
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;

    // Set rotation (+90 if the shape initially faces up)
    sprite.setRotation(angle);
}

sf::Vector2f Player::getCenter() const {
    sf::Vector2f center = sprite.getPosition();
    center.x += 20;
    center.y -= 20;
    return center;
}

void Player::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0;
}

int Player::getHealth() const {
    return currentHealth;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

bool Player::isAlive() const {
    return currentHealth > 0;
}

void Player::reset() {
    currentHealth = maxHealth;
    currentBullets = maxBullets;
    reloading = false;
    sprite.setPosition(960.f, 540.f);
}

bool Player::isReloading() const {
    return reloading;
}

int Player::getCurrentBullets() const {
    return currentBullets;
}

int Player::getMaxBullets() const {
    return maxBullets;
}

bool Player::canShoot() const {
    return !reloading && currentBullets > 0;
}

void Player::shoot() {
    if (canShoot()) {
        currentBullets--;
        if (currentBullets == 0) {
            reloading = true;
            reloadTimer = 0.f;
        }
    }
}

void Player::reload() {
    if (canShoot() && currentBullets < 12) {
        reloading = true;
        reloadTimer = 0.f;
    }
}

void Player::toggleSprint() {
    if (!isSprinting) {
        isSprinting = true;
    }
    else {
        isSprinting = false;
    }
}

void Player::updateReload(float deltaTime) {
    if (reloading) {
        reloadTimer += deltaTime;
        if (reloadTimer > reloadTime) {
            currentBullets = maxBullets;
            reloading = false;
            reloadTimer = 0.f;
        }
    }
}

bool Player::getSprinting() const {
    return isSprinting;
}

void Player::updateStamina(float deltaTime) {
    if (isSprinting && stamina > 0.f) {
        stamina -= staminaDrainRate * deltaTime;
        if (stamina < 0.f) stamina = 0.f;
    } else {
        stamina += staminaRegenRate * deltaTime;
        if (stamina > maxStamina) stamina = maxStamina;
    }

    if (stamina <= 0.f)
        isSprinting = false;
}

float Player::getStamina() const {
    return stamina;
}

float Player::getMaxStamina() const {
    return maxStamina;
}