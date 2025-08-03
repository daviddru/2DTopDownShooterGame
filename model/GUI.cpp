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

    ammoText.setFont(font);
    ammoText.setCharacterSize(20);
    ammoText.setFillColor(sf::Color::White);
    ammoText.setPosition(1700.f, 10.f);

    reloadText.setFont(font);
    reloadText.setCharacterSize(20);
    reloadText.setFillColor(sf::Color::Red);
    reloadText.setPosition(1700.f, 40.f);

    controls.setFont(font);
    controls.setCharacterSize(20);
    controls.setFillColor(sf::Color::White);
    controls.setPosition(1680.f, 1030.f);
    controls.setString("R to manual reload");
}

void GUI::updateHealth(int currentHealth, int maxHealth) {
    float healthPercent = static_cast<float>(currentHealth) / maxHealth;
    healthBar.setSize(sf::Vector2f(300.f * healthPercent, 20.f));

    healthText.setString(std::to_string(currentHealth) + " / " + std::to_string(maxHealth));
}

void GUI::updateAmmo(int currentBullets, int maxBullets, bool reloading) {
    ammoText.setString("Ammo: " + std::to_string(currentBullets) + " / " + std::to_string(maxBullets));

    if (reloading) {
        reloadText.setString("Reloading...");
    } else {
        reloadText.setString("");
    }
}

void GUI::draw(sf::RenderWindow& window) {
    window.draw(healthBarBackground);
    window.draw(healthBar);
    window.draw(healthText);

    window.draw(ammoText);
    if (!reloadText.getString().isEmpty())
        window.draw(reloadText);

    window.draw(controls);
}

void GUI::deathScreen(sf::RenderWindow& window) {
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::Red);

    sf::Text restartHint;
    restartHint.setFont(font);
    restartHint.setString("Press R to Restart");
    restartHint.setCharacterSize(24);
    restartHint.setFillColor(sf::Color::White);

    float windowWidth = static_cast<float>(window.getSize().x);

    // Center GAME OVER text
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.f, gameOverBounds.top + gameOverBounds.height / 2.f);
    gameOverText.setPosition(windowWidth / 2.f, 500.f);

    // Center restart hint text
    sf::FloatRect restartHintBounds = restartHint.getLocalBounds();
    restartHint.setOrigin(restartHintBounds.left + restartHintBounds.width / 2.f, restartHintBounds.top + restartHintBounds.height / 2.f);
    restartHint.setPosition(windowWidth / 2.f, 550.f);

    window.clear();
    window.draw(gameOverText);
    window.draw(restartHint);
    window.display();
}