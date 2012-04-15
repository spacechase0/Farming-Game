#include "Debug.h"

void Debug::initialize()
{
    text = sf::Text();
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
