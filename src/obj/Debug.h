#ifndef OBJ_DEBUG_H
#define OBJ_DEBUG_H

#include <string>

#include "obj/Base.h"

namespace obj
{
    class Debug : public Base
    {
        public:
        Debug( SceneGame& );

        void setText(const std::string&);
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


#endif // OBJ_DEBUG_H
