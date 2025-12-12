#include "Ball.h"
#include <cmath>

Ball::Ball() : x(0), y(0), predkoscX(0), predkoscY(0), promien(8.f) {
    ksztalt.setRadius(promien);
    ksztalt.setOrigin(promien, promien);
    ksztalt.setPosition(x, y);
    ksztalt.setFillColor(sf::Color::White);
}

Ball::Ball(float x_, float y_, float predkoscX_, float predkoscY_, float promien_)
    : x(x_), y(y_), predkoscX(predkoscX_), predkoscY(predkoscY_), promien(promien_)
{
    ksztalt.setRadius(promien);
    ksztalt.setOrigin(promien, promien);
    ksztalt.setPosition(x, y);
    ksztalt.setFillColor(sf::Color::White);
}

void Ball::move() {
    x += predkoscX;
    y += predkoscY;
    ksztalt.setPosition(x, y);
}

void Ball::bounceX() { predkoscX = -predkoscX; }
void Ball::bounceY() { predkoscY = -predkoscY; }

void Ball::collideWalls(float szerokoscOkna, float wysokoscOkna) {
    if (x - promien <= 0.f) { x = promien; bounceX(); }
    if (x + promien >= szerokoscOkna) { x = szerokoscOkna - promien; bounceX(); }
    if (y - promien <= 0.f) { y = promien; bounceY(); }
    // dolne odbicie: game over w Game
}

void Ball::bounceFromPaddle(const Paddle& paletka) {
    float top = paletka.getY() - paletka.getHeight() / 2.f;
    predkoscY = -std::abs(predkoscY);
    y = top - promien;
    ksztalt.setPosition(x, y);

    // utrzymanie stałej prędkości, modyfikujemy tylko predkoscX proporcjonalnie
    float relative = (x - paletka.getX()) / (paletka.getWidth() / 2.f);
    predkoscX = relative * std::sqrt(predkoscX * predkoscX + predkoscY * predkoscY);
}

void Ball::draw(sf::RenderTarget& target) {
    target.draw(ksztalt);
}

float Ball::getX() const { return x; }
float Ball::getY() const { return y; }
float Ball::getPredkoscX() const { return predkoscX; }
float Ball::getPredkoscY() const { return predkoscY; }
float Ball::getRadius() const { return promien; }

sf::FloatRect Ball::getBounds() const { return ksztalt.getGlobalBounds(); }
sf::Vector2f Ball::getPosition() const { return { x, y }; }
sf::Vector2f Ball::getVelocity() const { return { predkoscX, predkoscY }; }

void Ball::reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkosc) {
    x = pozycja.x; y = pozycja.y;
    predkoscX = predkosc.x; predkoscY = predkosc.y;
    ksztalt.setPosition(x, y);
}