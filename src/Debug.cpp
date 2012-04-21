#include "Debug.h"
#include <SFML/Config.hpp>

sf::String Debug::text;
sf::Font Debug::font;

void Debug::initialize()
{
    if (!font.loadFromFile("res/fonts/batang.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
}

void Debug::setText(const std::string& str)
{
    std::basic_string<sf::Uint32> tmp;
    sf::Utf<8>::toUtf32(str.begin(), str.end(), std::back_inserter(tmp));
    text = tmp;
}

void Debug::setText(const std::wstring& str)
{
    std::basic_string<sf::Uint32> tmp;
    sf::Utf<8>::toUtf32(str.begin(), str.end(), std::back_inserter(tmp));
    text = tmp;
}

void Debug::draw(sf::RenderWindow& window)
{
    sf::Text txt = sf::Text(text, font);
    window.draw(txt);
}
