#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(Paddle& paletka, Ball& pilka, std::vector<Stone>& bloki) {
    paddleX = paletka.getX();
    paddleY = paletka.getY();

    ballX = pilka.getX();
    ballY = pilka.getY();
    ballPredkoscX = pilka.getPredkoscX();
    ballPredkoscY = pilka.getPredkoscY();
    ballRadius = pilka.getRadius();

    stonesData.clear();
    for (const auto& blok : bloki) {
        StoneData sd;
        sd.x = blok.getX();
        sd.y = blok.getY();
        sd.hp = blok.getHP();
        sf::Color kolor = blok.getBounds().intersects(pilka.getBounds()) ? sf::Color::Red : sf::Color::White; // kolor
        sd.r = kolor.r;
        sd.g = kolor.g;
        sd.b = kolor.b;
        stonesData.push_back(sd);
    }
}

void GameState::apply(Paddle& paletka, Ball& pilka, std::vector<Stone>& bloki,
    float blockWidth, float blockHeight) {
    paletka.setPosition({ paddleX, paddleY });
    pilka.reset({ ballX, ballY }, { ballPredkoscX, ballPredkoscY });

    bloki.clear();
    for (const auto& sd : stonesData) {
        sf::Color kolor(sd.r, sd.g, sd.b);
        bloki.emplace_back(sd.x, sd.y, blockWidth, blockHeight, sd.hp, kolor);
    }
}

bool GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return false;

    file << paddleX << ' ' << paddleY << '\n';
    file << ballX << ' ' << ballY << ' ' << ballPredkoscX << ' ' << ballPredkoscY << ' ' << ballRadius << '\n';
    file << stonesData.size() << '\n';
    for (auto& s : stonesData) {
        file << s.x << ' ' << s.y << ' ' << s.hp << ' '
            << static_cast<int>(s.r) << ' '
            << static_cast<int>(s.g) << ' '
            << static_cast<int>(s.b) << '\n';
    }

    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;

    stonesData.clear();
    file >> paddleX >> paddleY;
    file >> ballX >> ballY >> ballPredkoscX >> ballPredkoscY >> ballRadius;

    size_t n;
    file >> n;
    for (size_t i = 0; i < n; ++i) {
        StoneData sd;
        int r, g, b;
        file >> sd.x >> sd.y >> sd.hp >> r >> g >> b;
        sd.r = static_cast<sf::Uint8>(r);
        sd.g = static_cast<sf::Uint8>(g);
        sd.b = static_cast<sf::Uint8>(b);
        stonesData.push_back(sd);
    }

    return true;
}