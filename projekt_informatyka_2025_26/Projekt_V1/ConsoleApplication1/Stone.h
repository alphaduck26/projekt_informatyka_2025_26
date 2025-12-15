#pragma once
#include <SFML/Graphics.hpp>

class Stone {
private:
    sf::RectangleShape shape;
    int hp;
    bool alive;

public:
    Stone();
    Stone(float x, float y, float szerokosc, float wysokosc, int hpStart, sf::Color kolor);

    void draw(sf::RenderTarget& target) const;
    bool collideWithBall(const sf::FloatRect& pilkaBounds) const;

    void hit();
    bool isAlive() const;
    int getHP() const;

    void setFillColor(const sf::Color& kolor);

    float getX() const;
    float getY() const;
    sf::FloatRect getBounds() const;
};