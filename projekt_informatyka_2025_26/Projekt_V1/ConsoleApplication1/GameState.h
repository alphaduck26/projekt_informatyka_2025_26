#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
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
    float ballPredkoscX, ballPredkoscY;
    float ballRadius;
    std::vector<StoneData> stonesData;

public:
    void capture(Paddle& paletka, Ball& pilka, std::vector<Stone>& bloki);
    void apply(Paddle& paletka, Ball& pilka, std::vector<Stone>& bloki,
        float blockWidth, float blockHeight);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
};