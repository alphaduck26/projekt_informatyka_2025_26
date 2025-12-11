#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<sf::Text> options;
    int selectedItem;
    sf::Font font;
    float startX, startY;
    float verticalSpacing;

public:
    Menu(unsigned int windowWidth, unsigned int windowHeight);

    void draw(sf::RenderTarget& target) const;

    void moveUp();
    void moveDown();
    void reset();

    int getSelectedItem() const { return selectedItem; }
};