#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f predkosc;

public:
    Ball();

    void reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkoscStart);
    void update();
    void draw(sf::RenderTarget& target) const;

    void bounceX();
    void bounceY();

    void setSpeed(float nowaPredkosc);
    void setRadius(float promien);

    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getRadius() const;

    sf::FloatRect getBounds() const;
};