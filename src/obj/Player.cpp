#include "obj/Player.h"

#include "Game.h"
#include "scenes/SceneGame.h"
#include "obj/TalkingNpc.h"
#include "obj/Entrance.h"
#include "util/Type.h"

namespace obj
{
	Player::Player( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2f thePos )
	   : Npc::Npc( theGame, theMap, theTexture, sf::Vector2i( 32, 64 ) ),
	     pressed{ false, false, false, false }
	{
		SetPosition( thePos );
	}

	void Player::Update()
	{
		const float speed = 3.25;
		
		Npc::Update();
		HandleKeyRelease();
		
		if ( pressed.left != pressed.right )
		{
			if ( pressed.left )
			{
				MoveInDirection( Left, speed );
			}
			if ( pressed.right )
			{
				MoveInDirection( Right, speed );
			}
		}
		if ( pressed.up != pressed.down )
		{
			if ( pressed.up )
			{
				MoveInDirection( Up, speed );
			}
			if ( pressed.down )
			{
				MoveInDirection( Down, speed );
			}
		}
	}

	void Player::Update( const sf::Event& event )
	{
		Npc::Update( event );
		if ( event.Type == sf::Event::KeyPressed )
		{
			if ( event.Key.Code == sf::Keyboard::Up )
			{
				pressed.up = true;
			}
			else if ( event.Key.Code == sf::Keyboard::Down )
			{
				pressed.down = true;
			}
			else if ( event.Key.Code == sf::Keyboard::Left )
			{
				pressed.left = true;
			}
			else if ( event.Key.Code == sf::Keyboard::Right )
			{
				pressed.right = true;
			}
			else if ( event.Key.Code == Game::PrimaryKey )
			{
				for ( auto it = map->objects.begin(); it != map->objects.end(); ++it )
				{
					if ( util::IsOfType< TalkingNpc* >( it->get() ) )
					{
						sf::FloatRect colRect = GetCollisionRect();
						MovementDirection dir = GetDirection();
						
						if ( dir == Up )
						{
							colRect.Top -= colRect.Height;
						}
						else if ( dir == Down )
						{
							colRect.Top += colRect.Height;
						}
						else if ( dir == Left )
						{
							colRect.Left -= colRect.Width;
						}
						else if ( dir == Right )
						{
							colRect.Left += colRect.Width;
						}
						
						TalkingNpc* npc = static_cast< TalkingNpc* >( it->get() );
						if ( npc->GetCollisionRect().Intersects( colRect ) )
						{
							npc->Talk();
							npc->FaceDirection( GetOppositeDirection() );
						}
					}
				}
			}
		}
		
	}

	void Player::Draw( sf::RenderWindow& window )
	{
		Npc::Draw( window );
	}
	
	void Player::CollidedWith( RenderObject* object )
	{
		if ( util::IsOfType< Entrance* >( object ) )
		{
			Entrance* entrance = static_cast< Entrance* >( object );
			game.maps.currentMap = entrance->GetDestination();
		}
	}
	
	void Player::HandleKeyRelease()
	{
		if ( pressed.up and !sf::Keyboard::IsKeyPressed( sf::Keyboard::Up ) )
		{
			pressed.up = false;
		}
		else if ( pressed.down and !sf::Keyboard::IsKeyPressed( sf::Keyboard::Down ) )
		{
			pressed.down = false;
		}
		else if ( pressed.left and !sf::Keyboard::IsKeyPressed( sf::Keyboard::Left ) )
		{
			pressed.left = false;
		}
		else if ( pressed.right and !sf::Keyboard::IsKeyPressed( sf::Keyboard::Right ) )
		{
			pressed.right = false;
		}
	}
}
