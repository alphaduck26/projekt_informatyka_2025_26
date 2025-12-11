#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float startX, float startY, float szer, float wys, float pred)
        : x(startX), y(startY), szerokosc(szer), wysokosc(wys), predkosc(pred)
    {
        shape.setSize({ szerokosc, wysokosc });
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
    }

    void moveLeft() { x -= predkosc; shape.setPosition(x, y); }
    void moveRight() { x += predkosc; shape.setPosition(x, y); }

    void clampToBounds(float width) {
        if (x - szerokosc / 2.f < 0) x = szerokosc / 2.f;
        if (x + szerokosc / 2.f > width) x = width - szerokosc / 2.f;
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) { target.draw(shape); }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};
