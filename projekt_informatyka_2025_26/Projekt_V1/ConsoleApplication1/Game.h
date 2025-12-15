#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Stone.h"

class Game {
private:
    Ball pilka;
    Paddle paletka;
    std::vector<Stone> bloki;

    int score;
    float scoreMultiplier;

    float szerokoscBloku;
    float wysokoscBloku;

public:
    Game();
    bool isBallLost(float windowHeight);
    void reset(float mnoznikPunktow);
    void update(float szerokoscOkna, float wysokoscOkna);
    void draw(sf::RenderTarget& target) const;

    void setScore(int s);
    int getScore() const;

    // gettery – TYLKO deklaracje
    Ball& getBall();
    Paddle& getPaddle();
    std::vector<Stone>& getStones();

    const Ball& getBall() const;
    const Paddle& getPaddle() const;
    const std::vector<Stone>& getStones() const;

    void setScoreMultiplier(float m);
    float getScoreMultiplier() const;

    float getBlockWidth() const;
    float getBlockHeight() const;
};