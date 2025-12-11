#include "Menu.h"
#include <iostream>

Menu::Menu(unsigned int windowWidth, unsigned int windowHeight)
    : selectedItem(0)
{
    // Załaduj font (musisz mieć plik arial.ttf w katalogu projektu)
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Blad wczytania fontu arial.ttf" << std::endl;
    }

    // Odstępy i pozycja początkowa
    const int numberOfOptions = 2;
    verticalSpacing = static_cast<float>(windowHeight) / (numberOfOptions + 1);
    startX = windowWidth / 2.f;
    startY = verticalSpacing;

    // Polskie napisy w menu
    std::vector<std::string> menuTexts = { "Nowa gra", "Wyjscie" };

    for (size_t i = 0; i < menuTexts.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuTexts[i]);
        text.setCharacterSize(30);
        text.setFillColor(i == selectedItem ? sf::Color::Yellow : sf::Color::White);
        text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
        text.setPosition(startX, startY + i * verticalSpacing);
        options.push_back(text);
    }
}

void Menu::draw(sf::RenderTarget& target) const {
    for (auto& option : options)
        target.draw(option);
}

void Menu::moveUp() {
    if (selectedItem > 0) {
        options[selectedItem].setFillColor(sf::Color::White);
        selectedItem--;
        options[selectedItem].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (selectedItem < static_cast<int>(options.size()) - 1) {
        options[selectedItem].setFillColor(sf::Color::White);
        selectedItem++;
        options[selectedItem].setFillColor(sf::Color::Yellow);
    }
}

void Menu::reset() {
    for (auto& option : options)
        option.setFillColor(sf::Color::White);
    selectedItem = 0;
    options[selectedItem].setFillColor(sf::Color::Yellow);
}