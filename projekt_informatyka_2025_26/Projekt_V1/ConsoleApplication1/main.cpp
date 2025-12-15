#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Game.h"
#include "GameState.h"

int main()
{
    const unsigned int WIDTH = 640;
    const unsigned int HEIGHT = 480;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(WIDTH, HEIGHT);
    Game game;
    GameState gamestate;

    enum class State { Menu, Playing, Scoreboard, Exiting };
    State state = State::Menu;
    bool gameStarted = false;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (state == State::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) menu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int sel = menu.getSelectedIndex();
                        if (sel == 0) { // Nowa gra
                            game.reset(menu.getScoreMultiplier());
                            gameStarted = false;
                            state = State::Playing;
                            float speedMul = menu.getSpeedMultiplier();
                            game.getBall().setSpeed(5.f * speedMul);
                            game.getPaddle().setSpeed(6.f * speedMul);
                            gameStarted = false;
                            state = State::Playing;
                        }
                        else if (sel == 1) { // Zmien trudnosc
                            int diff = static_cast<int>(menu.getDifficultyEnum());
                            diff = (diff + 1) % 4;
                            menu.setDifficulty(static_cast<Menu::Difficulty>(diff));
                        }
                        else if (sel == 2) { // Zapisz gre
                            gamestate.capture(game);
                            if (gamestate.saveToFile("save.txt")) std::cout << "Gra zapisana\n";
                        }
                        else if (sel == 3) { // Wczytaj gre
                            if (gamestate.loadFromFile("save.txt")) {
                                gamestate.apply(game, menu.getSpeedMultiplier());
                                gameStarted = false;
                                state = State::Playing;
                                std::cout << "Gra wczytana\n";
                            }
                            else std::cout << "Brak zapisu\n";
                        }
                        else if (sel == 4) { // Tabela wynikow
                            state = State::Scoreboard;
                        }
                        else if (sel == 5) { // Wyjscie
                            window.close();
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
                        menu.checkStarClick(pos);
                    }
                }
            }
            else if (state == State::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        state = State::Menu;
                    }
                    else if (event.key.code == sf::Keyboard::Space) {
                        gameStarted = true;
                    }
                }
            }
            else if (state == State::Scoreboard) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    state = State::Menu;
                }
            }
        }

        sf::Time dt = clock.restart();

        if (state == State::Playing && gameStarted) {
            game.update(WIDTH, HEIGHT);
            // Sprawdzenie, czy piłka spadła poniżej dolnej krawędzi okna
            if (game.getBall().getY() - game.getBall().getRadius() > HEIGHT) {
                gameStarted = false;    // zatrzymanie gry
                state = State::Menu;    // powrót do menu

                // Wyświetlenie komunikatu "Miss! Koniec gry"
                sf::Font font;
                if (!font.loadFromFile("arial.ttf")) font.loadFromFile("arial.ttf");

                sf::Text missText;
                missText.setFont(font);
                missText.setCharacterSize(30);
                missText.setFillColor(sf::Color::Red);
                missText.setString("Miss! Koniec gry");
                missText.setPosition(WIDTH / 2.f - 100.f, HEIGHT / 2.f - 20.f);

                window.clear(sf::Color(20, 20, 30));
                window.draw(missText);
                window.display();

                sf::sleep(sf::seconds(2.f)); // krótka pauza, żeby gracz zdążył zobaczyć komunikat

                // Reset gry do domyślnych ustawień
                game.reset(menu.getScoreMultiplier());
            }
        }

        menu.updateStar(WIDTH, HEIGHT);

        window.clear(sf::Color(20, 20, 30));
        if (state == State::Menu) menu.draw(window);
        else if (state == State::Playing) {
            game.draw(window);

            // feedback trudnosci
            sf::Font font;
            if (!font.loadFromFile("arial.ttf")) font.loadFromFile("arial.ttf");
            sf::Text diffText;
            diffText.setFont(font);
            diffText.setCharacterSize(20);
            diffText.setFillColor(sf::Color::Cyan);

            std::string diffLabel;
            switch (menu.getDifficultyEnum()) {
            case Menu::Difficulty::Easy: diffLabel = "Easy"; break;
            case Menu::Difficulty::Medium: diffLabel = "Medium"; break;
            case Menu::Difficulty::Hard: diffLabel = "Hard"; break;
            case Menu::Difficulty::Extreme: diffLabel = "Extreme"; break;
            }

            diffText.setString("Trudnosc: " + diffLabel);
            diffText.setPosition(10.f, 10.f);
            window.draw(diffText);

            // punkty
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setCharacterSize(20);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setString("Score: " + std::to_string(game.getScore()));
            scoreText.setPosition(10.f, 35.f);
            window.draw(scoreText);
        }
        else if (state == State::Scoreboard) {
            sf::Font font;
            if (!font.loadFromFile("arial.ttf")) font.loadFromFile("arial.ttf");
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);

            std::ifstream file("scores.txt");
            float y = 50.f;
            std::string line;
            while (std::getline(file, line)) {
                text.setString(line);
                text.setPosition(50.f, y);
                window.draw(text);
                y += 30.f;
            }
        }
        window.display();
    }
    return 0;
}