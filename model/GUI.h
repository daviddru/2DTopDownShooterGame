//
// Created by david on 7/31/2025.
//

#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

class GUI {
private:
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;
    sf::Font font;
    sf::Text healthText;

    sf::Text ammoText;
    sf::Text reloadText;

public:
    GUI();

    void updateHealth(int currentHealth, int maxHealth);
    void updateAmmo(int currentBullets, int maxBullets, bool reloading);
    void draw(sf::RenderWindow& window);
    void deathScreen(sf::RenderWindow& window);
};



#endif //GUI_H
