#include "Paddle.h"
#include <SFML/Window.hpp>

Paddle::Paddle() : predkosc(6.f) {
    shape.setSize({ 120.f, 20.f });
    shape.setOrigin(60.f, 10.f);
    shape.setPosition(320.f, 440.f);
    shape.setFillColor(sf::Color::Green);
}

void Paddle::setPosition(const sf::Vector2f& pozycja) { shape.setPosition(pozycja); }
void Paddle::setSpeed(float nowaPredkosc) { predkosc = nowaPredkosc; }

void Paddle::moveLeft() { shape.move(-predkosc, 0.f); }
void Paddle::moveRight() { shape.move(predkosc, 0.f); }

void Paddle::update(float szerokoscOkna) {
    handleInput();
    sf::Vector2f pos = shape.getPosition();
    float polowa = shape.getSize().x / 2.f;
    if (pos.x - polowa < 0.f) shape.setPosition(polowa, pos.y);
    if (pos.x + polowa > szerokoscOkna) shape.setPosition(szerokoscOkna - polowa, pos.y);
}

//void Paddle::setSpeed(float s) {
  //  predkosc = s;
//}


void Paddle::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveRight();
}

void Paddle::draw(sf::RenderTarget& target) const { target.draw(shape); }
sf::FloatRect Paddle::getBounds() const { return shape.getGlobalBounds(); }
sf::Vector2f Paddle::getPosition() const { return shape.getPosition(); }
float Paddle::getX() const { return shape.getPosition().x; }
float Paddle::getY() const { return shape.getPosition().y; }