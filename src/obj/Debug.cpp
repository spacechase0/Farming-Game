#include "obj/Debug.h"

namespace obj
{
    Debug::Debug( SceneGame& game )
       : Base( game ),
         enabled( true )
    {
    }

    void Debug::setText( const std::string& msg )
    {
        text.SetString( msg );
    }

    std::string Debug::getText() const
    {
        return text.GetString();
    }

    void Debug::setColor( sf::Color color )
    {
        text.SetColor( color );
    }

    sf::Color Debug::getColor() const
    {
        return text.GetColor();
    }

    void Debug::setSize( unsigned int size )
    {
        text.SetCharacterSize( size );
    }

    unsigned int Debug::getSize() const
    {
        return text.GetCharacterSize();
    }

    void Debug::Update()
	{
	}

	void Debug::Update( const sf::Event& event )
	{
	}

    void Debug::Draw( sf::RenderWindow& window )
	{
	    if ( enabled )
	    {
	        window.Draw( text );
        }
	}
}
