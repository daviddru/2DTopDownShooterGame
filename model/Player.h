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

    float speed = 150.f;
    int maxHealth = 100.f;
    int currentHealth = 100.f;

    int maxBullets = 12;
    int currentBullets = 12;
    bool reloading = false;
    float reloadTime = 2.f;
    float reloadTimer = 0.f;

    bool isSprinting = false;
    float sprintSpeed = 300.f;
    float stamina = 100.f;
    float maxStamina = 100.f;
    float staminaRegenRate = 10.f;
    float staminaDrainRate = 50.f;


public:
    Player();

    void handleInput(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);
    void update(sf::RenderWindow& window, float deltaTime);
    void takeDamage(int damage);
    void reset();

    void updateReload(float deltaTime);
    bool canShoot() const;
    void shoot();
    void reload();
    void toggleSprint();
    void updateStamina(float deltaTime);

    sf::Vector2f getPosition() const;
    sf::Vector2f getCenter() const;
    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;

    int getCurrentBullets() const;
    int getMaxBullets() const;
    bool isReloading() const;

    bool getSprinting() const;
    float getStamina() const;
    float getMaxStamina() const;
};



#endif //PLAYER_H
