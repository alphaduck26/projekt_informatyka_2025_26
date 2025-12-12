#include "Stone.h"
#include "Ball.h"

Stone::Stone()
    : x(0), y(0), szerokosc(0), wysokosc(0), hp(1), alive(false)
{
    ksztalt.setSize({ 0.f, 0.f });
}

Stone::Stone(float x_, float y_, float szer_, float wys_, int hp_, const sf::Color& kolor)
    : x(x_), y(y_), szerokosc(szer_), wysokosc(wys_), hp(hp_), alive(true)
{
    ksztalt.setSize({ szerokosc, wysokosc });
    ksztalt.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    ksztalt.setPosition(x, y);
    ksztalt.setFillColor(kolor);
    ksztalt.setOutlineColor(sf::Color::Black);
    ksztalt.setOutlineThickness(1.f);
}

void Stone::draw(sf::RenderTarget& target) {
    if (alive) target.draw(ksztalt);
}

bool Stone::isAlive() const { return alive; }
void Stone::setAlive(bool val) { alive = val; }

int Stone::getHP() const { return hp; }
void Stone::setHP(int val) { hp = val; }

void Stone::hit() {
    hp--;
    if (hp <= 0) alive = false;
}

void Stone::setOutlineColor(const sf::Color& kolor) { ksztalt.setOutlineColor(kolor); }
void Stone::setOutlineThickness(float t) { ksztalt.setOutlineThickness(t); }

float Stone::getX() const { return x; }
float Stone::getY() const { return y; }
sf::FloatRect Stone::getBounds() const { return ksztalt.getGlobalBounds(); }

void Stone::collideWithBall(Ball& pilka) {
    if (!alive) return;
    if (!pilka.getBounds().intersects(ksztalt.getGlobalBounds())) return;

    // proste odbicie Y/X w zależności od miejsca uderzenia
    float overlapLeft = pilka.getX() + pilka.getRadius() - (x - szerokosc / 2.f);
    float overlapRight = (x + szerokosc / 2.f) - (pilka.getX() - pilka.getRadius());
    float overlapTop = pilka.getY() + pilka.getRadius() - (y - wysokosc / 2.f);
    float overlapBottom = (y + wysokosc / 2.f) - (pilka.getY() - pilka.getRadius());

    bool odbijX = std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom);

    if (odbijX) pilka.bounceX();
    else pilka.bounceY();

    hit();
}