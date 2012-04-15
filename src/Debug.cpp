#include "Debug.h"

sf::Text Debug::text;

void Debug::initialize()
{
    text.setColor(sf::Color::Yellow);
}

void Debug::setText(std::string str)
{
    text.setString(str);
}

void Debug::draw(sf::RenderWindow& window)
{
    window.draw(text);
}
