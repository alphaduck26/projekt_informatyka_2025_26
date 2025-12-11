#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

class Game {
private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;
    bool m_gameOver;

public:
    Game();

    void update(sf::Time dt);
    void render(sf::RenderTarget& target);

    bool isGameOver() const;
    void reset();
};