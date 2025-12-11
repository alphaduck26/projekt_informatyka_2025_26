#include "Stone.h"

Stone::Stone(float startX, float startY, float w, float h, sf::Color color)
    : x(startX), y(startY), width(w), height(h), alive(true)
{
    shape.setSize({ width, height });
    shape.setOrigin(width / 2.f, height / 2.f);
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

void Stone::draw(sf::RenderTarget& target) {
    target.draw(shape);
}

bool Stone::collide(const Pilka& pilka) {
    float left = x - width / 2.f;
    float right = x + width / 2.f;
    float top = y - height / 2.f;
    float bottom = y + height / 2.f;

    float px = pilka.getX();
    float py = pilka.getY();
    float r = pilka.getRadius();

    if (px + r < left || px - r > right) return false;
    if (py + r < top || py - r > bottom) return false;

    return true;
}