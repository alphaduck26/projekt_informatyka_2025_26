#include "Game.h"
#include <iostream>

const sf::Color BLOCK_COLORS[4] = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow
};

Game::Game()
    : m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
    m_pilka(320.f, 200.f, 4.f, 3.f, 8.f),
    m_gameOver(false)
{
    const int rows = 5;
    const int cols = 10;
    const float startY = 50.f;

    const float blockWidth = 640.f / cols;
    const float blockHeight = 25.f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = col * blockWidth + blockWidth / 2.f;
            float y = startY + row * blockHeight + blockHeight / 2.f;

            sf::Color color = BLOCK_COLORS[row % 4];

            Stone block(x, y, blockWidth, blockHeight, color);
            block.setOutlineColor(sf::Color::Black);
            block.setOutlineThickness(1.f);

            m_bloki.push_back(block);
        }
    }
}

void Game::update(sf::Time dt) {
    if (m_gameOver) return;

    m_pilka.move();
    m_pilka.collideWalls(640.f, 480.f);

    if (m_pilka.collidePaddle(m_paletka))
        std::cout << "HIT PADDLE\n";

    for (auto& block : m_bloki) {
        if (block.isAlive() && block.collide(m_pilka)) {
            block.setAlive(false);
            m_pilka.bounceY();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(640.f);

    if (m_pilka.getY() - m_pilka.getRadius() > 480.f)
        m_gameOver = true;
}

void Game::render(sf::RenderTarget& target) {
    m_paletka.draw(target);
    m_pilka.draw(target);
    for (auto& block : m_bloki)
        if (block.isAlive())
            block.draw(target);
}

bool Game::isGameOver() const {
    return m_gameOver;
}

void Game::reset() {
    m_paletka = Paletka(320.f, 440.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(320.f, 200.f, 4.f, 3.f, 8.f);

    for (auto& block : m_bloki)
        block.setAlive(true);

    m_gameOver = false;
}