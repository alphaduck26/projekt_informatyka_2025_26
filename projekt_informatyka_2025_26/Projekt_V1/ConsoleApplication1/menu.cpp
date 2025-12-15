#include "Menu.h"
#include <iostream>

Menu::Menu(unsigned int windowWidth, unsigned int windowHeight)
    : selected(0), scoreMultiplier(1.f)
{
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Cannot load font arial.ttf\n";
    }

    std::vector<std::string> labels = {
        "Nowa gra",
        "Zmien trudnosc",
        "Zapisz gre",
        "Wczytaj gre",
        "Tabela wynikow",
        "Wyjscie"
    };
    items.clear();

    startX = windowWidth / 2.f;
    spacing = static_cast<float>(windowHeight) / (labels.size() + 1);
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
    star.draw(target);

    // feedback trudnosci w menu
    sf::Text diffText;
    diffText.setFont(font);
    diffText.setCharacterSize(24);
    diffText.setFillColor(sf::Color::Cyan);

    std::string diffLabel;
    switch (difficulty) {
    case Difficulty::Easy: diffLabel = "Easy"; break;
    case Difficulty::Medium: diffLabel = "Medium"; break;
    case Difficulty::Hard: diffLabel = "Hard"; break;
    case Difficulty::Extreme: diffLabel = "Extreme"; break;
    }
    diffText.setString(diffLabel);
    diffText.setPosition(items[1].getPosition().x + 200.f, items[1].getPosition().y - 15.f);
    target.draw(diffText);
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
    star.reset();
    scoreMultiplier = 1.f;
}

void Menu::updateStar(float szerokoscOkna, float wysokoscOkna) {
    star.update(szerokoscOkna, wysokoscOkna);
}

bool Menu::checkStarClick(const sf::Vector2f& mousePos) {
    if (star.handleClick(mousePos)) {
        scoreMultiplier = 2.f;
        std::cout << "Gwiazda kliknieta! Punkty x2\n";
        return true;
    }
    return false;
}

float Menu::getSpeedMultiplier() const {
    switch (difficulty) {
    case Difficulty::Easy: return 0.8f;
    case Difficulty::Medium: return 1.0f;
    case Difficulty::Hard: return 1.3f;
    case Difficulty::Extreme: return 1.6f;
    }
    return 1.f;
}