#include "Paletka.h"

Paletka::Paletka(float startX, float startY, float szer, float wys, float speed)
    : x(startX), y(startY), szerokosc(szer), wysokosc(wys), predkosc(speed)
{
    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Paletka::moveLeft() {
    x -= predkosc;
    shape.setPosition(x, y);
}

void Paletka::moveRight() {
    x += predkosc;
    shape.setPosition(x, y);
}

void Paletka::clampToBounds(float width) {
    if (x - szerokosc / 2.f < 0) x = szerokosc / 2.f;
    if (x + szerokosc / 2.f > width) x = width - szerokosc / 2.f;
    shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}