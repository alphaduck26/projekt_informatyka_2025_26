// main.cpp
// Jeden wspólny program uruchamiający oba zadania:
// 1) symulacja odbić piłki
// 2) ruch paletki po osi X

#include <iostream>
#include "Pilka.h"
#include "Paletka.h"

using namespace std;

void symulacjaPilki(string opis, Pilka p) {
    cout << "\n=== " << opis << " ===\n";
    const int W = 640;
    const int H = 480;

    for (int i = 1; i <= 30; i++) {
        p.przesun();
        string e = p.kolizjaSciana(W, H);

        cout << "Krok " << i
            << ": x=" << p.getX()
            << ", y=" << p.getY()
            << ", vx=" << p.getVx()
            << ", vy=" << p.getVy();

        if (!e.empty()) cout << " " << e;
        cout << endl;
    }
}

void symulacjaPaletki() {
    cout << "\n=== Symulacja ruchu paletki ===\n";

    const int W = 640;

    Paletka pal(320, 450, 80, 10);

    for (int i = 1; i <= 100; i++) {

        if (i % 20 < 10)
            pal.przesunLewo();
        else
            pal.przesunPrawo();

        pal.ograniczRuch(W);

        int half = pal.getSzerokosc() / 2;
        bool lewa = (pal.getX() - half <= 0);
        bool prawa = (pal.getX() + half >= W);

        cout << "Krok " << i
            << ": x=" << pal.getX()
            << ", y=" << pal.getY();

        if (lewa)  cout << " LEWA GRANICA";
        if (prawa) cout << " PRAWA GRANICA";

        cout << endl;
    }
}

int main() {

    // === ZADANIE 1 – trzy demonstracje odbić piłki ===
    Pilka p1(5, 200, -5, 0, 4);
    symulacjaPilki("A) Odbicie od lewej/prawej sciany", p1);

    Pilka p2(200, 5, 0, -6, 4);
    symulacjaPilki("B) Odbicie od gornej/dolnej sciany", p2);

    Pilka p3(10, 10, -5, 4, 6);
    symulacjaPilki("C) Kolejne odbicia pod katem", p3);

    // === ZADANIE 2 – ruch paletki ===
    symulacjaPaletki();

    return 0;
}