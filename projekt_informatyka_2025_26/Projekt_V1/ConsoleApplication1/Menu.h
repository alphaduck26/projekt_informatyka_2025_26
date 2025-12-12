#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<sf::Text> items;
    sf::Font font;
    int selected;
    float startX, startY;
    float spacing;

public:
    Menu(unsigned int szerokoscOkna, unsigned int wysokoscOkna);

    void draw(sf::RenderTarget& target) const;
    void moveUp();
    void moveDown();
    void reset();

    int getSelectedIndex() const { return selected; }
};