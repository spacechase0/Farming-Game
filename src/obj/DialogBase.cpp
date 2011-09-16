#include "obj/DialogBase.h"

namespace obj
{
	DialogBase::DialogBase( SceneGame& theGame, sf::Texture& theBackgroundTexture )
	   : Base::Base( theGame ),
	     backgroundTexture( &theBackgroundTexture ),
	     sprite( theBackgroundTexture )
	{
	}
			
	void SetPosition( sf::Vector2f pos )
	{
		sprite.SetPosition( pos );
	}
	
	void SetPosition( float x, float y )
	{
		sprite.SetPosition( x, y );
	}
	
	sf::Vector2f GetPosition() const
	{
		return sprite.GetPosition();
	}

	void DialogBase::Update()
	{
		for ( auto it = gui.begin(); it != gui.end(); ++it )
		{
			( * it )->Update();
		}
	}
	
	void DialogBase::Update( const sf::Event& event )
	{
		for ( auto it = gui.begin(); it != gui.end(); ++it )
		{
			( * it )->Update( event );
		}
	}
	
	void DialogBase::Draw( sf::RenderWindow& window )
	{
		for ( auto it = gui.begin(); it != gui.end(); ++it )
		{
			( * it )->Draw( window );
		}
	}
}
