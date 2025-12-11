#include "Pilka.h"
#include <cmath>

Pilka::Pilka(float startX, float startY, float speedX, float speedY, float r)
    : x(startX), y(startY), vx(speedX), vy(speedY), radius(r)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Pilka::move() {
    x += vx;
    y += vy;
    shape.setPosition(x, y);
}

void Pilka::bounceX() {
    vx = -vx;
}

void Pilka::bounceY() {
    vy = -vy;
}

void Pilka::collideWalls(float width, float height) {
    if (x - radius <= 0.f) {
        x = radius;
        bounceX();
    }
    else if (x + radius >= width) {
        x = width - radius;
        bounceX();
    }

    if (y - radius <= 0.f) {
        y = radius;
        bounceY();
    }
}

bool Pilka::collidePaddle(const Paletka& p) {
    float left = p.getX() - p.getSzerokosc() / 2.f;
    float right = p.getX() + p.getSzerokosc() / 2.f;
    float top = p.getY() - p.getWysokosc() / 2.f;

    if (x >= left && x <= right && y + radius >= top && y - radius < top) {
        vy = -std::abs(vy);
        y = top - radius;
        shape.setPosition(x, y);
        return true;
    }
    return false;
}

void Pilka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}