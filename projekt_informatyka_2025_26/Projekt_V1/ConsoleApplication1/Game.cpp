#include "Game.h"
#include <algorithm>
#include <iostream>

static constexpr float WINDOW_WIDTH = 640.f;
static constexpr float WINDOW_HEIGHT = 480.f;

Game::Game()
    : m_paddle(320.f, 440.f, 120.f, 20.f, 8.f),
    m_ball(320.f, 240.f, 3.5f, -3.5f, 8.f)
{
    restart();
}

void Game::restart() {
    m_gameOver = false;

    m_paddle = Paddle(320.f, 440.f, 120.f, 20.f, 8.f);
    m_ball = Ball(320.f, 240.f, 3.5f, -3.5f, 8.f);

    const int kolumny = 10;
    const int wiersze = 5;
    m_blockWidth = WINDOW_WIDTH / static_cast<float>(kolumny);
    m_blockHeight = 30.f;

    m_bloki.clear();
    const float startY = 60.f;

    for (int r = 0; r < wiersze; ++r) {
        for (int c = 0; c < kolumny; ++c) {
            float cx = c * m_blockWidth + m_blockWidth / 2.f;
            float cy = startY + r * m_blockHeight + m_blockHeight / 2.f;
            sf::Color kolor;
            switch (r % 4) {
            case 0: kolor = sf::Color::Red; break;
            case 1: kolor = sf::Color::Yellow; break;
            case 2: kolor = sf::Color::Green; break;
            default: kolor = sf::Color::Blue; break;
            }
            m_bloki.emplace_back(cx, cy, m_blockWidth, m_blockHeight, 1, kolor);
        }
    }
}

void Game::update(sf::Time dt) {
    if (m_gameOver) return;

    m_ball.move();
    m_ball.collideWalls(WINDOW_WIDTH, WINDOW_HEIGHT);

    // paddle control
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paddle.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paddle.moveRight();
    m_paddle.clampToBounds(WINDOW_WIDTH);

    // bounce from paddle
    if (m_ball.getBounds().intersects(m_paddle.getBounds()) && m_ball.getPredkoscY() > 0.f) {
        m_ball.bounceFromPaddle(m_paddle);
    }

    // blocks collision
    for (auto& blok : m_bloki) {
        if (blok.isAlive()) {
            blok.collideWithBall(m_ball);
        }
    }

    // remove dead blocks
    m_bloki.erase(std::remove_if(m_bloki.begin(), m_bloki.end(),
        [](const Stone& s) { return !s.isAlive(); }), m_bloki.end());

    // check game over
    if (m_ball.getY() - m_ball.getRadius() > WINDOW_HEIGHT) {
        m_gameOver = true;
    }
}

void Game::render(sf::RenderTarget& target) {
    m_paddle.draw(target);
    m_ball.draw(target);
    for (auto& b : m_bloki) b.draw(target);
}

bool Game::isGameOver() const { return m_gameOver; }