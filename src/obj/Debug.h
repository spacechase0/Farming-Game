#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include "obj/Base.h"

namespace obj
{
    class Debug : public Base
    {
        public:
        Debug( SceneGame& );

        void setText(std::string);
        std::string getText() const;
        void setColor(sf::Color);
        sf::Color getColor() const;
        void setSize(unsigned int);
        unsigned int getSize() const;

        virtual void Update();
        virtual void Update( const sf::Event& event );
        virtual void Draw( sf::RenderWindow& window );

        private:
        sf::Text text;
        sf::Font* font;

        bool enabled;
    };
}


#endif // DEBUG_H
