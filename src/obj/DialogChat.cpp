#include "obj/DialogChat.h"

#include "scenes/SceneGame.h"
#include "Game.h"

namespace obj
{
	DialogChat::DialogChat( SceneGame& theGame, sf::Texture& theBackgroundTexture, sf::Texture& theButtonTexture, sf::Font& theFont, const std::vector< std::string >& theText )
	   : DialogBase::DialogBase( theGame, theBackgroundTexture ),
	     displayFont( &theFont ),
	     display( theText[ 0 ], theFont, 20 ),
	     buttonTexture( &theButtonTexture ),
	     button( theButtonTexture ),
	     text( theText ),
	     currentText( 0 ),
	     justMade( true )
	{
		SetPosition( 0, Game::WindowSize.y - backgroundTexture->GetHeight() );
		
		display.SetPosition( 16, sprite.GetPosition().y + 16 );
		
		button.SetOrigin( buttonTexture->GetWidth() / 2, buttonTexture->GetHeight() / 2 );
		button.SetPosition( Game::WindowSize.x - 32, Game::WindowSize.y - 24 );
	}
	
	void DialogChat::Update()
	{
		justMade = false;
	}
	
	void DialogChat::Update( const sf::Event& event )
	{
		DialogBase::Update( event );
		if ( event.Type == sf::Event::KeyPressed )
		{
			if ( event.Key.Code == sf::Keyboard::Z and !justMade )
			{
				if ( currentText + 1 >= text.size() )
				{
					CloseDialog();
				}
				else
				{
					display.SetString( text[ ++currentText ] );
				}
			}
		}
	}
	
	void DialogChat::Draw( sf::RenderWindow& window )
	{
		DialogBase::Draw( window );
		window.Draw( display );
		window.Draw( button );
	}
	
	void DialogChat::CloseDialog()
	{
		game.simulateWorld = true;
		for ( auto it = game.maps.menuObjects.begin(); it != game.maps.menuObjects.end(); ++it )
		{
			if ( !( * it ) )
			{
				continue;
			}
			
			obj::Base* obj = it->get();
			if ( obj == this )
			{
				game.maps.AddMenuGarbage( it );
				return;
			}
		}
	}
}
