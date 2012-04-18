#ifndef DEBUG_H
#define DEBUG_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Debug
{
    static sf::String text;
    static sf::Font font;

    public:
    static void initialize();
    static void setText(std::string);
    static void setText(std::wstring);
    static void showMessage(std::string);
    static void showMessage(std::wstring);
    static void draw(sf::RenderWindow&);
};

#endif
