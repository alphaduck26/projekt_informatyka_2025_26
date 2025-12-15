#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Star.h"

class Menu {
private:
    std::vector<sf::Text> items;
    sf::Font font;
    int selected;
    float startX, startY;
    float spacing;

    Star star;
    float scoreMultiplier;

public:
    enum class Difficulty { Easy, Medium, Hard, Extreme };
    Difficulty difficulty = Difficulty::Easy;

    Menu(unsigned int windowWidth, unsigned int windowHeight);

    void draw(sf::RenderTarget& target) const;
    void moveUp();
    void moveDown();
    void reset();

    void updateStar(float szerokoscOkna, float wysokoscOkna);
    bool checkStarClick(const sf::Vector2f& mousePos);

    int getSelectedIndex() const { return selected; }
    void setDifficulty(Difficulty d) { difficulty = d; }
    Difficulty getDifficultyEnum() const { return difficulty; }
    float getScoreMultiplier() const { return scoreMultiplier; }
    float getSpeedMultiplier() const;
};