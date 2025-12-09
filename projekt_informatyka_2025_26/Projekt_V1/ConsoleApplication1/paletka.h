// Paletka.h
// Klasa reprezentująca poziomą paletkę (jak w Arkanoidzie).

#ifndef PALETKA_H
#define PALETKA_H

#include <iostream>

class Paletka {
private:
    int x;
    int y;
    int szerokosc;
    int vx;

public:
    Paletka(int x_, int y_, int s_, int v_)
        : x(x_), y(y_), szerokosc(s_), vx(v_) {}

    void przesunLewo() {
        x -= vx;
    }

    void przesunPrawo() {
        x += vx;
    }

    void ograniczRuch(int width) {
        int half = szerokosc / 2;
        if (x - half < 0) x = half;
        if (x + half > width) x = width - half;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getSzerokosc() const { return szerokosc; }
};

#endif