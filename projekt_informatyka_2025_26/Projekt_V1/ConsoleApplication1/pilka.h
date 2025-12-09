// Pilka.h
// Klasa reprezentująca piłkę poruszającą się w pudełku 640x480.

#ifndef PILKA_H
#define PILKA_H

#include <iostream>
#include <string>

class Pilka {
private:
    int x, y;       // pozycja środka piłki
    int vx, vy;     // prędkości
    int radius;     // promień

public:
    Pilka(int startX, int startY, int vX, int vY, int r)
        : x(startX), y(startY), vx(vX), vy(vY), radius(r) {}

    void przesun() {
        x += vx;
        y += vy;
    }

    void odbijX() { vx = -vx; }
    void odbijY() { vy = -vy; }

    std::string kolizjaSciana(int width, int height) {
        std::string e = "";

        if (x - radius <= 0 || x + radius >= width) {
            odbijX();
            e += "HIT X-WALL";
        }
        if (y - radius <= 0 || y + radius >= height) {
            if (!e.empty()) e += " ";
            odbijY();
            e += "HIT Y-WALL";
        }
        return e;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getVx() const { return vx; }
    int getVy() const { return vy; }
    int getRadius() const { return radius; }
};

#endif