#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Stone.h"

class Game {
private:
    Paddle m_paddle;
    Ball m_ball;
    std::vector<Stone> m_bloki;
    bool m_gameOver;

    float m_blockWidth;
    float m_blockHeight;

public:
    Game();

    void restart();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);

    bool isGameOver() const;

    // getters for GameState
    Paddle& getPaddle() { return m_paddle; }
    Ball& getBall() { return m_ball; }
    std::vector<Stone>& getBlocks() { return m_bloki; }

    float getBlockWidth() const { return m_blockWidth; }
    float getBlockHeight() const { return m_blockHeight; }
};