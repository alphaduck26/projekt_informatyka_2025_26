#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Stone.h"

struct StoneData {
    float x, y;
    int hp;
    sf::Uint8 r, g, b;
};

class GameState {
private:
    float paddleX, paddleY;
    float ballX, ballY;
    int score;
    std::vector<StoneData> stones;

public:
    void capture(const Game& game);
    void apply(Game& game, float speedMultiplier);

    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
};