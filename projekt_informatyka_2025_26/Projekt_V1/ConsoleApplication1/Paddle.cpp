#include "Paddle.h"

Paddle::Paddle(float startX, float startY, float szer, float wys, float pred)
    : x(startX), y(startY), szerokosc(szer), wysokosc(wys), predkosc(pred)
{
    ksztalt.setSize({ szerokosc, wysokosc });
    ksztalt.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    ksztalt.setPosition(x, y);
    ksztalt.setFillColor(sf::Color::Green);
}

void Paddle::moveLeft() {
    x -= predkosc;
    ksztalt.setPosition(x, y);
}

void Paddle::moveRight() {
    x += predkosc;
    ksztalt.setPosition(x, y);
}

void Paddle::clampToBounds(float szerokoscOkna) {
    if (x - szerokosc / 2.f < 0.f)
        x = szerokosc / 2.f;
    if (x + szerokosc / 2.f > szerokoscOkna)
        x = szerokoscOkna - szerokosc / 2.f;

    ksztalt.setPosition(x, y);
}

void Paddle::draw(sf::RenderTarget& target) const {
    target.draw(ksztalt);
}

float Paddle::getX() const { return x; }
float Paddle::getY() const { return y; }
float Paddle::getWidth() const { return szerokosc; }
float Paddle::getHeight() const { return wysokosc; }

sf::FloatRect Paddle::getBounds() const { return ksztalt.getGlobalBounds(); }

void Paddle::setPosition(const sf::Vector2f& pozycja) {
    x = pozycja.x;
    y = pozycja.y;
    ksztalt.setPosition(x, y);
}