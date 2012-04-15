#include "Debug.h"

sf::Text Debug::text;

void Debug::initialize()
{
    text.setColor(sf::Color::Yellow);
    text.move(100, 100);
    text.setScale(2, 2);
    text.setCharacterSize(30);
}

void Debug::setText(std::string str)
{
    text.setString(str);
}

void Debug::draw(sf::RenderWindow& window)
{
    window.draw(text);
}
