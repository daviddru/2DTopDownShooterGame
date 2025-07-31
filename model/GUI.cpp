//
// Created by david on 7/31/2025.
//

#include "GUI.h"
#include <iostream>

GUI::GUI() {
    healthBarBackground.setSize(sf::Vector2f(300.f, 20.f));
    healthBarBackground.setFillColor(sf::Color::Red);
    healthBarBackground.setPosition(10.f, 10.f);

    healthBar.setSize(sf::Vector2f(300.f, 20.f));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(10.f, 10.f);

    if (!font.loadFromFile("../model/assets/fonts/GoogleSansCode-Bold.ttf")) {
        std::cerr << "Failed to load font for GUI\n";
    }

    healthText.setFont(font);
    healthText.setCharacterSize(14);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition(120.f, 12.f);
}

void GUI::update(int currentHealth, int maxHealth) {
    float healthPercent = static_cast<float>(currentHealth) / maxHealth;
    healthBar.setSize(sf::Vector2f(300.f * healthPercent, 20.f));

    healthText.setString(std::to_string(currentHealth) + " / " + std::to_string(maxHealth));
}

void GUI::draw(sf::RenderWindow& window) {
    window.draw(healthBarBackground);
    window.draw(healthBar);
    window.draw(healthText);
}