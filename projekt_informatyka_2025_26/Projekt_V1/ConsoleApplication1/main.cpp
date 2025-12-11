#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paletka.h"
#include "Pilka.h"

int main() {
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow window({ (unsigned)WIDTH, (unsigned)HEIGHT }, "Arkanoid test");
    window.setFramerateLimit(60);

    Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f);
    Pilka pilka(320.f, 200.f, 4.f, 3.f, 8.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Sterowanie paletką
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            pal.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            pal.moveRight();
        pal.clampToBounds(WIDTH);

        // Aktualizacja piłki
        pilka.move();
        pilka.collideWalls(WIDTH, HEIGHT);
        if (pilka.collidePaddle(pal))
            std::cout << "HIT PADDLE\n";

        // Sprawdzenie przegranej
        if (pilka.getY() - pilka.getRadius() > HEIGHT) {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
        }

        // Debug info
        static int frameCounter = 0;
        if (++frameCounter % 30 == 0) {
            std::cout << "x=" << pilka.getX()
                << " y=" << pilka.getY()
                << " vx=" << pilka.getVx()
                << " vy=" << pilka.getVy() << std::endl;
        }

        // Rysowanie
        window.clear(sf::Color(20, 20, 30));
        pal.draw(window);
        pilka.draw(window);
        window.display();
    }

    return 0;
}