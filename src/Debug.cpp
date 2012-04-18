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
    /*std::size_t size = sf::Utf< 8 >::count( str.begin(), str.end() );

    std::vector< sf::Uint32 > c;
    c.resize( size );

    sf::Utf< 8 >::toUtf32( str.begin(), str.end(), c.begin() );

    sf::String strr( &c[ 0 ] );*/

    std::basic_string<sf::Uint32> tmp;

    sf::Utf<8>::toUtf32( str.begin(), str.end(), std::back_inserter( tmp ) );

    text = tmp;
}

void Debug::setText(const std::wstring& str)
{
    /*std::size_t size = sf::Utf< 8 >::count( str.begin(), str.end() );

    std::vector< sf::Uint32 > c;
    c.resize( size );

    sf::Utf< 8 >::toUtf32( str.begin(), str.end(), c.begin() );

    sf::String strr( &c[ 0 ] );*/

    std::basic_string<sf::Uint32> tmp;

    sf::Utf<8>::toUtf32( str.begin(), str.end(), std::back_inserter( tmp ) );

    text = tmp;
}

void Debug::draw(sf::RenderWindow& window)
{
    sf::Text txt = sf::Text(text, font);
    window.draw(txt);
}
