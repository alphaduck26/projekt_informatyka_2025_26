#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball {
private:
    float x, y;
    float predkoscX, predkoscY;
    float promien;
    sf::CircleShape ksztalt;

public:
    Ball();
    Ball(float x_, float y_, float predkoscX_, float predkoscY_, float promien_);

    void move();
    void bounceX();
    void bounceY();

    void collideWalls(float szerokoscOkna, float wysokoscOkna);
    void bounceFromPaddle(const Paddle& paletka);

    void draw(sf::RenderTarget& target);

    float getX() const;
    float getY() const;
    float getPredkoscX() const;
    float getPredkoscY() const;
    float getRadius() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    void reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkosc);
};