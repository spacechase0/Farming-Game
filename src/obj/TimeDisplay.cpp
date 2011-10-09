#include "obj/TimeDisplay.h"

#include "scenes/SceneGame.h"
#include "Game.h"

namespace obj
{
	TimeDisplay::TimeDisplay( SceneGame& theGame )
	   : Base::Base( theGame )
	{
		const sf::Color sunrise( 241, 174, 79, 75 );
		const sf::Color sunset( 241, 174, 79, 75 );
		const sf::Color day( 255, 255, 255, 0 );
		const sf::Color night( 9, 11, 36, 200 );
		
		ColorScale scale;
		scale.insert( 0.00, night );
		scale.insert( 0.25, night );
		scale.insert( 0.29, sunrise );
		scale.insert( 0.295, day );
		scale.insert( 0.755, day );
		scale.insert( 0.76, sunset );
		scale.insert( 0.80, night );
		scale.insert( 1.00, night );
		
		timeGradient.Create( 1, 30000 / 5 );
		scale.draw( timeGradient, sf::Vector2f( 0, 0 ), sf::Vector2f( 0, 30000 / 5 ), GradientStyle::Linear, 30000 / 5 );
	}
	
	void TimeDisplay::Draw( sf::RenderWindow& window )
	{
		int px = ( game.GetTime() / 5 );
		sf::Color mix = timeGradient.GetPixel( 0, px );
		
		sf::Shape shape = sf::Shape::Rectangle( 0, 0, Game::WindowSize.x + 2, Game::WindowSize.y + 1, mix );
		shape.SetBlendMode( sf::Blend::Alpha );
		window.Draw( shape );
	}
	
	int TimeDisplay::GetDepth() const
	{
		return 25;
	}
}

