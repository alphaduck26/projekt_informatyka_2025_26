#pragma once
#include <SFML/Graphics.hpp>
class Ball; // forward declaration

class Stone {
private:
    float x, y;
    float szerokosc, wysokosc;
    int hp;
    bool alive;
    sf::RectangleShape ksztalt;

public:
    Stone();
    Stone(float x_, float y_, float szer_, float wys_, int hp_, const sf::Color& kolor = sf::Color::White);

    void draw(sf::RenderTarget& target);
    bool isAlive() const;
    void setAlive(bool val);

    int getHP() const;
    void setHP(int val);

    void hit();

    void setOutlineColor(const sf::Color& kolor);
    void setOutlineThickness(float t);

    float getX() const;
    float getY() const;
    sf::FloatRect getBounds() const;

    void collideWithBall(Ball& pilka);
};