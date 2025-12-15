#include "Ball.h"
#include <cmath>

Ball::Ball() {
    shape.setRadius(8.f);
    shape.setOrigin(8.f, 8.f);
    shape.setFillColor(sf::Color::White);
    predkosc = { 1.f, -1.f };
}

void Ball::reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkoscStart) {
    shape.setPosition(pozycja);
    predkosc = predkoscStart;
}

void Ball::update() { shape.move(predkosc); }
void Ball::draw(sf::RenderTarget& target) const { target.draw(shape); }

void Ball::bounceX() { predkosc.x = -predkosc.x; }
void Ball::bounceY() { predkosc.y = -predkosc.y; }

void Ball::setSpeed(float nowaPredkosc) {
    float len = std::sqrt(predkosc.x * predkosc.x + predkosc.y * predkosc.y);
    if (len == 0.f) return;
    predkosc = (predkosc / len) * nowaPredkosc;
}

void Ball::setRadius(float promien) {
    shape.setRadius(promien);
    shape.setOrigin(promien, promien);
}

float Ball::getX() const { return shape.getPosition().x; }
float Ball::getY() const { return shape.getPosition().y; }
float Ball::getVx() const { return predkosc.x; }
float Ball::getVy() const { return predkosc.y; }
float Ball::getRadius() const { return shape.getRadius(); }

sf::FloatRect Ball::getBounds() const { return shape.getGlobalBounds(); }