#include "Stone.h"

Stone::Stone() : hp(0), alive(false) { shape.setSize({ 0.f, 0.f }); }

Stone::Stone(float x, float y, float szerokosc, float wysokosc, int hpStart, sf::Color kolor)
    : hp(hpStart), alive(true) {
    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    shape.setPosition(x, y);
    shape.setFillColor(kolor);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);
}

void Stone::draw(sf::RenderTarget& target) const { if (alive) target.draw(shape); }
bool Stone::collideWithBall(const sf::FloatRect& pilkaBounds) const {
    if (!alive) return false;
    return pilkaBounds.intersects(shape.getGlobalBounds());
}

void Stone::hit() {
    if (!alive) return;
    hp--;
    if (hp <= 0) { hp = 0; alive = false; }
}

bool Stone::isAlive() const { return alive; }
int Stone::getHP() const { return hp; }
void Stone::setFillColor(const sf::Color& kolor) { shape.setFillColor(kolor); }

float Stone::getX() const { return shape.getPosition().x; }
float Stone::getY() const { return shape.getPosition().y; }
sf::FloatRect Stone::getBounds() const { return shape.getGlobalBounds(); }