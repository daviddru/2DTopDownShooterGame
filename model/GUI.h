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

public:
    GUI();

    void update(int currentHealth, int maxHealth);
    void draw(sf::RenderWindow& window);
    void deathScreen(sf::RenderWindow& window);
};



#endif //GUI_H
