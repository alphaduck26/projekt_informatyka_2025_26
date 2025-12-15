#pragma once
#include <SFML/Graphics.hpp>

class Star {
private:
    sf::ConvexShape shape;
    sf::Vector2f predkosc;
    bool aktywna;

public:
    Star();

    void update(float szerokoscOkna, float wysokoscOkna);
    void draw(sf::RenderTarget& target) const;

    bool handleClick(const sf::Vector2f& mysz);
    void reset();

    bool isActive() const;
};