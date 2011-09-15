#include "obj/Player.h"

#include "Game.h"

namespace obj
{
	const float Player::RenderOffsetThreshold  = Game::TileSize;
	const float Player::RenderOffsetMultiplier = 3.25;
	
	Player::Player( Game& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos )
	   : GridObject::GridObject( theGame, theTexture, theGridPos )
	{
		sprite.SetSubRect( sf::IntRect( 0, 0, texture->GetWidth(), texture->GetHeight() ) );
	}
	
	void Player::Update()
	{
		GridObject::Update();
		if ( movement != None )
		{
			renderOffset += ( Game::SimulationRate / Game::TileSize ) * RenderOffsetMultiplier;
			if ( renderOffset >= RenderOffsetThreshold )
			{
				renderOffset -= RenderOffsetThreshold;
				switch ( movement )
				{
					case Up:    --gridPos.y; break;
					case Down:  ++gridPos.y; break;
					case Left:  --gridPos.x; break;
					case Right: ++gridPos.x; break;
					default:    break; // Gets rid of "warning: enumeration value 'None' not handled in switch"
				}
				SetGridPosition( gridPos ); // Take a look at GridObject::SetGridPosition to see why. :P
				movement = nextDir;
			}
		}
		else
		{
			renderOffset = 0.00;
			movement = nextDir;
		}
	}
	
	void Player::Update( const sf::Event& event )
	{
		GridObject::Update( event );
		if ( event.Type == sf::Event::KeyPressed )
		{
			switch ( event.Key.Code )
			{
				#define DoKey(a) case sf::Keyboard::a: \
									nextDir = a;       \
									break;
				
				DoKey( Up );
				DoKey( Down );
				DoKey( Left );
				DoKey( Right );
				
				#undef DoKey
				
				default:
					break;
			};
		}
		else 
		if ( event.Type == sf::Event::KeyReleased )
		{
			switch ( event.Key.Code )
			{
				#define DoKey(a) case sf::Keyboard::a:  \
									if ( nextDir == a ) \
									{                   \
										nextDir = None; \
									}                   \
									break;
				
				DoKey( Up );
				DoKey( Down );
				DoKey( Left );
				DoKey( Right );
				
				#undef DoKey
				
				default:
					break;
			};
		}
	}
	
	void Player::Draw( sf::RenderWindow& window )
	{
		float moveX = 0.f, moveY = 0.f;
		switch ( movement )
		{
			case Up:    moveY = -renderOffset; break;
			case Down:  moveY = renderOffset;  break;
			case Left:  moveX = -renderOffset; break;
			case Right: moveX = renderOffset;  break;
			default: break;
		}
		
		sprite.Move( moveX, moveY );
		GridObject::Draw( window );
		sprite.Move( -moveX, -moveY );
	}
}
