#include "obj/WeatherDisplay.h"

#include "scenes/SceneGame.h"
#include "Game.h"

namespace obj
{
	WeatherDisplay::WeatherDisplay( SceneGame& theGame, sf::Texture& theRainTexture )
	   : Base::Base( theGame ),
	     weatherHeight( 0 ),
	     rainTexture( theRainTexture )
	{
	}
	
	void WeatherDisplay::Draw( sf::RenderWindow& window )
	{
		if ( game.GetWeather() == SceneGame::None )
		{
			return;
		}
		
		weatherHeight += 350 * ( window.GetFrameTime() / 1000.f );
		while ( weatherHeight > Game::WindowSize.y - 64 )
		{
			weatherHeight -= Game::WindowSize.y - 64;
		}
		
		for ( size_t i = 0; i < Game::WindowSize.x; i += 64 )
		{
			sf::Texture* tex = NULL;
			if ( game.GetWeather() == SceneGame::Rain )
			{
				tex = &rainTexture;
			}
			
			sf::Sprite top( * tex );
			sf::Sprite bottom( * tex );
			
			top.SetPosition( i, weatherHeight - tex->GetHeight() );
			bottom.SetPosition( i, weatherHeight );
			
			window.Draw( top );
			window.Draw( bottom );
		}
	}
	
	int WeatherDisplay::GetDepth() const
	{
		return 50;
	}
}


