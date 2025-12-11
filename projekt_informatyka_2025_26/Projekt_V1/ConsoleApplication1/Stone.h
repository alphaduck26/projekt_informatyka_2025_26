#pragma once
#include <SFML/Graphics.hpp>
#include "Pilka.h"

class Stone {
private:
    float x, y;
    float width, height;
    bool alive;
    sf::RectangleShape shape;

public:
    Stone(float startX, float startY, float w, float h, sf::Color color);

    void draw(sf::RenderTarget& target);
    bool collide(const Pilka& pilka);

    bool isAlive() const { return alive; }
    void setAlive(bool val) { alive = val; }

    void setOutlineColor(const sf::Color& color) { shape.setOutlineColor(color); }
    void setOutlineThickness(float thickness) { shape.setOutlineThickness(thickness); }
};