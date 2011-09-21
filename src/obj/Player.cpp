#include "obj/Player.h"

#include "Game.h"
#include "scenes/SceneGame.h"

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
		Npc::Update();
		if ( pressed.up )
		{
			Walk( Up, 3.25 );
		}
		if ( pressed.down )
		{
			Walk( Down, 3.25 );
		}
		if ( pressed.left )
		{
			Walk( Left, 3.25 );
		}
		if ( pressed.right )
		{
			Walk( Right, 3.25 );
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
				std::vector< std::string > str;
				str.push_back( "Hello World!" );
				game.CreateChatDialog( str );
			}
		}
		else if ( event.Type == sf::Event::KeyReleased )
		{
			if ( event.Key.Code == sf::Keyboard::Up )
			{
				pressed.up = false;
			}
			else if ( event.Key.Code == sf::Keyboard::Down )
			{
				pressed.down = false;
			}
			else if ( event.Key.Code == sf::Keyboard::Left )
			{
				pressed.left = false;
			}
			else if ( event.Key.Code == sf::Keyboard::Right )
			{
				pressed.right = false;
			}
		}
	}

	void Player::Draw( sf::RenderWindow& window )
	{
		Npc::Draw( window );
	}
}
