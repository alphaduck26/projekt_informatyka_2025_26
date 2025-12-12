#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape ksztalt;

public:
    Paddle(float startX, float startY, float szer, float wys, float pred);

    void moveLeft();
    void moveRight();
    void clampToBounds(float szerokoscOkna);

    void draw(sf::RenderTarget& target) const;

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& pozycja);
};