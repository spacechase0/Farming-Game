#include "obj/Player.h"

#include "Game.h"

namespace obj
{
	Player::Player( Game& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos )
	   : Npc::Npc( theGame, theTexture, sf::Vector2i( 32, 64 ) )
	{
		SetGridPosition( theGridPos );
	}
	
	void Player::Update()
	{
		Npc::Update();
	}
	
	void Player::Update( const sf::Event& event )
	{
		Npc::Update( event );
		if ( event.Type == sf::Event::KeyPressed )
		{
			switch ( event.Key.Code )
			{
				#define DoKey(a) case sf::Keyboard::a: \
									Walk( a );         \
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
		else if ( event.Type == sf::Event::KeyReleased )
		{
			switch ( event.Key.Code )
			{
				#define DoKey(a) case sf::Keyboard::a:  \
									if ( nextDir == a ) \
									{                   \
										StopWalking();  \
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
		Npc::Draw( window );
	}
}
