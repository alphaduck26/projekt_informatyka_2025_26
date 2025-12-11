#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.h"
#include <cmath>

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float startX, float startY, float velX, float velY, float r)
        : x(startX), y(startY), vx(velX), vy(velY), radius(r)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition(x, y);
    }

    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0) { x = radius; bounceX(); }
        if (x + radius >= width) { x = width - radius; bounceX(); }
        if (y - radius <= 0) { y = radius; bounceY(); }
        // Dół: brak odbicia, obsługiwane w main()
        shape.setPosition(x, y);
    }

    bool collidePaddle(const Paletka& p) {
        float palX = p.getX();
        float palY = p.getY();
        float palW = p.getSzerokosc();
        float palH = p.getWysokosc();

        if (x >= palX - palW / 2.f && x <= palX + palW / 2.f) {
            if (y + radius >= palY - palH / 2.f && y - radius < palY - palH / 2.f) {
                vy = -std::abs(vy);
                y = (palY - palH / 2.f) - radius;
                shape.setPosition(x, y);
                return true;
            }
        }
        return false;
    }

    void draw(sf::RenderTarget& target) { target.draw(shape); }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};