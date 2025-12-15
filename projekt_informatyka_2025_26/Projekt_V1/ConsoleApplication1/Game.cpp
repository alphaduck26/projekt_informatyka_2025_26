#include "Game.h"
#include <algorithm>
#include <cmath>

Game::Game()
    : score(0),
    scoreMultiplier(1.f),
    szerokoscBloku(64.f),
    wysokoscBloku(30.f)
{
    reset(1.f);
}

void Game::reset(float mnoznikPunktow)
{
    score = 0;
    scoreMultiplier = mnoznikPunktow;

    paletka.setPosition({ 320.f, 440.f });
    bloki.clear();

    pilka.reset(
        { paletka.getX(), paletka.getY() - paletka.getBounds().height / 2.f - pilka.getRadius() - 1.f },
        { 0.f, -5.f } // początkowa prędkość w górę
    );

    const int cols = 10;
    const int rows = 5;

    szerokoscBloku = 640.f / cols;
    wysokoscBloku = 30.f;

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            int hp = 3 - (r % 3);

            sf::Color kolor =
                (hp == 3) ? sf::Color::Blue :
                (hp == 2) ? sf::Color::Yellow :
                sf::Color::Red;

            bloki.emplace_back(
                c * szerokoscBloku + szerokoscBloku / 2.f,
                60.f + r * wysokoscBloku,
                szerokoscBloku,
                wysokoscBloku,
                hp,
                kolor
            );
        }
    }
}

bool Game::isBallLost(float windowHeight)
{
    return pilka.getY() - pilka.getRadius() > windowHeight;
}

void Game::update(float szerokoscOkna, float wysokoscOkna)
{
    pilka.update();
    paletka.update(szerokoscOkna);

    sf::FloatRect p = pilka.getBounds();

    if (p.left <= 0 || p.left + p.width >= szerokoscOkna)
        pilka.bounceX();

    if (p.top <= 0)
        pilka.bounceY();

    // odbicie od paletki (kąt zależny od miejsca)
    if (pilka.getBounds().intersects(paletka.getBounds()))
    {
        float offset = pilka.getX() - paletka.getX();
        float halfWidth = paletka.getBounds().width / 2.f;

        float angle = (offset / halfWidth) * 75.f;
        float rad = angle * 3.14159265f / 180.f;

        float speed = std::sqrt(
            pilka.getVx() * pilka.getVx() +
            pilka.getVy() * pilka.getVy()
        );

        pilka.reset(
            { pilka.getX(), pilka.getY() },
            { speed * std::sin(rad), -speed * std::cos(rad) }
        );
    }

    // kolizje z blokami
    for (auto& blk : bloki)
    {
        if (!blk.isAlive())
            continue;

        if (blk.collideWithBall(pilka.getBounds()))
        {
            blk.hit();

            sf::FloatRect b = blk.getBounds();
            sf::FloatRect k = pilka.getBounds();

            float overlapX = std::min(
                (k.left + k.width) - b.left,
                (b.left + b.width) - k.left
            );

            float overlapY = std::min(
                (k.top + k.height) - b.top,
                (b.top + b.height) - k.top
            );

            if (overlapX < overlapY)
                pilka.bounceX();
            else
                pilka.bounceY();

            int hp = blk.getHP();
            if (hp == 2) blk.setFillColor(sf::Color::Yellow);
            if (hp == 1) blk.setFillColor(sf::Color::Red);

            score += static_cast<int>(10 * scoreMultiplier);
            break;
        }
    }

    bloki.erase(
        std::remove_if(
            bloki.begin(),
            bloki.end(),
            [](const Stone& s) { return !s.isAlive(); }
        ),
        bloki.end()
    );
}

void Game::draw(sf::RenderTarget& target) const
{
    paletka.draw(target);
    pilka.draw(target);

    for (const auto& b : bloki)
        b.draw(target);
}

// ===================== GETTERY / SETTERY =====================

int Game::getScore() const
{
    return score;
}

void Game::setScore(int s)
{
    score = s;
}

Ball& Game::getBall()
{
    return pilka;
}

const Ball& Game::getBall() const
{
    return pilka;
}

Paddle& Game::getPaddle()
{
    return paletka;
}

const Paddle& Game::getPaddle() const
{
    return paletka;
}

std::vector<Stone>& Game::getStones()
{
    return bloki;
}

const std::vector<Stone>& Game::getStones() const
{
    return bloki;
}

float Game::getBlockWidth() const
{
    return szerokoscBloku;
}

float Game::getBlockHeight() const
{
    return wysokoscBloku;
}