#ifndef DEBUG_H
#define DEBUG_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Debug
{
    static sf::Text text;

    public:
    static void initialize();
    static void setText(std::string);
    static void draw(sf::RenderWindow&);
};

#endif
