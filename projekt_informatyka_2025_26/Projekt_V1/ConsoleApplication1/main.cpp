#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "GameState.h"

int main() {
    const unsigned int windowWidth = 640;
    const unsigned int windowHeight = 480;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(windowWidth, windowHeight);
    Game game;

    enum class State { Menu, Playing, Exiting };
    State state = State::Menu;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    state = State::Menu;
            }

            if (state == State::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) menu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int sel = menu.getSelectedIndex();
                        if (sel == 0) {
                            game.restart();
                            state = State::Playing;
                        }
                        else if (sel == 1) {
                            GameState gs;
                            if (gs.loadFromFile("zapis.txt")) {
                                gs.apply(game.getPaddle(), game.getBall(), game.getBlocks(),
                                    game.getBlockWidth(), game.getBlockHeight());
                                state = State::Playing;
                                std::cout << "Loaded saved game\n";
                            }
                            else {
                                std::cout << "No save file found (zapis.txt)\n";
                            }
                        }
                        else if (sel == 2) {
                            window.close();
                        }
                    }
                }
            }
            else if (state == State::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::F5) {
                        GameState gs;
                        gs.capture(game.getPaddle(), game.getBall(), game.getBlocks());
                        if (gs.saveToFile("zapis.txt")) std::cout << "Game saved (zapis.txt)\n";
                        else std::cout << "Save error!\n";
                    }
                }
            }
        }

        sf::Time dt = clock.restart();

        if (state == State::Playing) {
            game.update(dt);
            for (auto& blok : game.getBlocks()) {
                if (blok.isAlive()) {
                    blok.collideWithBall(game.getBall());
                }
            }

            if (game.isGameOver()) {
                state = State::Menu;
                menu.reset();
            }
        }

        window.clear(sf::Color(20, 20, 30));
        if (state == State::Menu) menu.draw(window);
        else if (state == State::Playing) game.render(window);
        window.display();
    }

    return 0;
}