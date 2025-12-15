#include "Star.h"

Star::Star() : aktywna(true), predkosc(2.5f, 2.0f) {
    shape.setPointCount(10);
    shape.setPoint(0, { 0.f, -20.f });
    shape.setPoint(1, { 6.f, -6.f });
    shape.setPoint(2, { 20.f, 0.f });
    shape.setPoint(3, { 6.f, 6.f });
    shape.setPoint(4, { 0.f, 20.f });
    shape.setPoint(5, { -6.f, 6.f });
    shape.setPoint(6, { -20.f, 0.f });
    shape.setPoint(7, { -6.f, -6.f });
    shape.setPoint(8, { 0.f, -20.f });
    shape.setPoint(9, { 0.f, 0.f });

    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(320.f, 240.f);
}

void Star::update(float szerokoscOkna, float wysokoscOkna) {
    if (!aktywna) return;
    shape.move(predkosc);
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 20.f || pos.x > szerokoscOkna - 20.f) predkosc.x *= -1.f;
    if (pos.y < 20.f || pos.y > wysokoscOkna - 20.f) predkosc.y *= -1.f;
}

bool Star::handleClick(const sf::Vector2f& mysz) {
    if (!aktywna) return false;
    if (shape.getGlobalBounds().contains(mysz)) {
        aktywna = false;
        return true;
    }
    return false;
}

void Star::reset() {
    aktywna = true;
    shape.setPosition(320.f, 240.f);
}

bool Star::isActive() const { return aktywna; }

void Star::draw(sf::RenderTarget& target) const {
    if (aktywna) target.draw(shape);
}