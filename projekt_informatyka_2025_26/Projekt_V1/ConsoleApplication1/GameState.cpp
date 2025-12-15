#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(const Game& game) {
    paddleX = game.getPaddle().getX();
    paddleY = game.getPaddle().getY();

    ballX = game.getBall().getX();
    ballY = game.getBall().getY();

    stones.clear();
    for (const auto& s : game.getStones()) {
        if (!s.isAlive()) continue;

        StoneData sd;
        sd.x = s.getX();
        sd.y = s.getY();
        sd.hp = s.getHP();

        // kolor po HP
        if (sd.hp == 3) { sd.r = 0; sd.g = 0; sd.b = 255; }       // Blue
        else if (sd.hp == 2) { sd.r = 255; sd.g = 255; sd.b = 0; } // Yellow
        else if (sd.hp == 1) { sd.r = 255; sd.g = 0; sd.b = 0; }   // Red

        stones.push_back(sd);
    }

    score = game.getScore();
}

void GameState::apply(Game& game, float speedMultiplier) {
    game.getPaddle().setPosition({ paddleX, paddleY });
    game.getPaddle().setSpeed(6.f * speedMultiplier);

    game.getBall().reset(
        { ballX, ballY },
        {5.f * speedMultiplier, -5.f * speedMultiplier }
    );

    std::vector<Stone>& bloki = game.getStones();
    bloki.clear();
    for (const auto& sd : stones) {
        sf::Color c(sd.r, sd.g, sd.b);
        bloki.emplace_back(sd.x, sd.y, game.getBlockWidth(), game.getBlockHeight(), sd.hp, c);
    }

    game.setScore(score);
}

bool GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return false;

    file << paddleX << " " << paddleY << "\n";
    file << ballX << " " << ballY << "\n";
    file << score << "\n";
    file << stones.size() << "\n";

    for (const auto& s : stones) {
        file << s.x << " " << s.y << " " << s.hp << " "
            << int(s.r) << " " << int(s.g) << " " << int(s.b) << "\n";
    }
    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;

    size_t n;
    file >> paddleX >> paddleY;
    file >> ballX >> ballY;
    file >> score;
    file >> n;

    stones.clear();
    for (size_t i = 0; i < n; ++i) {
        StoneData sd;
        int r, g, b;
        file >> sd.x >> sd.y >> sd.hp >> r >> g >> b;
        sd.r = sf::Uint8(r);
        sd.g = sf::Uint8(g);
        sd.b = sf::Uint8(b);
        stones.push_back(sd);
    }
    return true;
}