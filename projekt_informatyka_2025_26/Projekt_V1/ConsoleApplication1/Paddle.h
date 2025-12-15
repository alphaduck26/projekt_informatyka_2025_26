#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float predkosc;

public:
    Paddle();

    void update(float szerokoscOkna);
    void draw(sf::RenderTarget& target) const;

    void moveLeft();
    void moveRight();

   // void setSpeed(float s);
    void setSpeed(float nowaPredkosc);
    void setPosition(const sf::Vector2f& pozycja);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    float getX() const;
    float getY() const;

    void handleInput();
};