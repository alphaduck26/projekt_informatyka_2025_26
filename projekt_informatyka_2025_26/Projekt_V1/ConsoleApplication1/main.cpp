#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Menu.h"

enum class GameState { Menu, Playing, Exiting };

int main()
{
    const unsigned int WIDTH = 640;
    const unsigned int HEIGHT = 480;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid");
    window.setFramerateLimit(60);

    Game game;
    Menu menu(WIDTH, HEIGHT);

    GameState currentState = GameState::Menu;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::Menu;
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    if (currentState == GameState::Menu) {
                        if (menu.getSelectedItem() == 0) {
                            game.reset();
                            currentState = GameState::Playing;
                        }
                        else if (menu.getSelectedItem() == 1) {
                            currentState = GameState::Exiting;
                        }
                    }
                }

                if (currentState == GameState::Menu) {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down)
                        menu.moveDown();
                }
            }
        }

        if (currentState == GameState::Playing) {
            game.update(dt);
            if (game.isGameOver())
                currentState = GameState::Menu;
        }

        window.clear(sf::Color(20, 20, 30));

        if (currentState == GameState::Menu)
            menu.draw(window);
        else if (currentState == GameState::Playing)
            game.render(window);

        window.display();

        if (currentState == GameState::Exiting)
            window.close();
    }

    return 0;
}