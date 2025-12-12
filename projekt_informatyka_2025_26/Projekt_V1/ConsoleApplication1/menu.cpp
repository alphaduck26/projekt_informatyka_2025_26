#include "Menu.h"
#include <iostream>

Menu::Menu(unsigned int szerokoscOkna, unsigned int wysokoscOkna)
    : selected(0)
{
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Cannot load font arial.ttf\n";
    }

    std::vector<std::string> labels = { "Nowa gra", "Wczytaj gre", "Wyjscie" };
    items.clear();

    startX = szerokoscOkna / 2.f;
    spacing = static_cast<float>(wysokoscOkna) / (labels.size() + 1);
    startY = spacing;

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text t;
        t.setFont(font);
        t.setString(labels[i]);
        t.setCharacterSize(36);
        t.setFillColor(i == static_cast<size_t>(selected) ? sf::Color::Yellow : sf::Color::White);

        sf::FloatRect bounds = t.getLocalBounds();
        t.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        t.setPosition(startX, startY + i * spacing);
        items.push_back(t);
    }
}

void Menu::draw(sf::RenderTarget& target) const {
    for (const auto& t : items) target.draw(t);
}

void Menu::moveUp() {
    if (selected > 0) {
        items[selected].setFillColor(sf::Color::White);
        selected--;
        items[selected].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (selected < static_cast<int>(items.size()) - 1) {
        items[selected].setFillColor(sf::Color::White);
        selected++;
        items[selected].setFillColor(sf::Color::Yellow);
    }
}

void Menu::reset() {
    for (auto& t : items) t.setFillColor(sf::Color::White);
    selected = 0;
    if (!items.empty()) items[0].setFillColor(sf::Color::Yellow);
}