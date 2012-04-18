#include "Debug.h"
#include <SFML/Config.hpp>
#include <Windows.h>

sf::String Debug::text;
sf::Font Debug::font;

void Debug::initialize()
{
    if (!font.loadFromFile("res/fonts/batang.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
}

void Debug::setText(std::string str)
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

void Debug::setText(std::wstring str)
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

void Debug::showMessage(std::string str)
{
    MessageBox(NULL, str.c_str(), NULL, NULL);
}

void Debug::showMessage(std::wstring str)
{
    //MessageBox(NULL, str.c_str(), NULL, NULL);
}

void Debug::draw(sf::RenderWindow& window)
{
    sf::Text txt = sf::Text(text, font);
    window.draw(txt);
}
