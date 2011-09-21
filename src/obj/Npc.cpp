#include "obj/Npc.h"

#include "Game.h"
#include "scenes/SceneGame.h"

namespace obj
{
	Npc::Npc( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2i theFrameSize )
	   : RenderObject::RenderObject( theGame, theTexture, sf::Vector2f( 0, 0 ) ),
	     map( &theMap ),
	     frameSize( theFrameSize )
	{
		sf::IntRect subRect( frameSize.x * Down, frameSize.y * 0, frameSize.x, frameSize.y );
		sprite.SetSubRect( subRect );
	}
	
	void Npc::Update()
	{
		RenderObject::Update();
		/*
		if ( movement != None and IsDirectionEmpty( movement ) )
		{
			Movement( Up,    'y', -1 );
			Movement( Down,  'y',  1 );
			Movement( Left,  'x', -1 );
			Movement( Right, 'x',  1 );
		}
		//*/
	}
	
	void Npc::Update( const sf::Event& event )
	{
		RenderObject::Update( event );
	}
	
	void Npc::Draw( sf::RenderWindow& window )
	{
		RenderObject::Draw( window );
	}
	
	void Npc::Walk( MovementDirection theMovement, float speed )
	{
		if ( !IsDirectionEmpty( theMovement ) )
		{
			return;
		}
		
		switch ( theMovement )
		{
			case Up:
				Movement( theMovement, 'y', -speed );
				break;
			
			case Down:
				Movement( theMovement, 'y',  speed );
				break;
			
			case Left:
				Movement( theMovement, 'x', -speed );
				break;
			
			case Right:
				Movement( theMovement, 'x',  speed );
				break;
			
			default:
				break;
		}
	}
	
	sf::Vector2i Npc::GetGridPosition() const
	{
		sf::Vector2i gridPos( sprite.GetPosition().x, sprite.GetPosition().y );
		gridPos -= sf::Vector2i( Game::TileSize / 2, Game::TileSize / 2 );
		gridPos.x /= Game::TileSize;
		gridPos.y /= Game::TileSize;
		return gridPos;
	}
	
	bool Npc::IsDirectionEmpty( MovementDirection& dir, float speed ) const
	{
		sf::Vector2f pos = sprite.GetPosition();
		switch ( dir )
		{
			case Up:
				pos.y -= speed;
				break;
			
			case Down:
				pos.y += Game::TileSize + speed;
				break;
			
			case Left:
				pos.x -= speed;
				break;
			
			case Right:
				pos.x += Game::TileSize + speed;
				break;
			
			// Gets rid of "warning: enumeration value 'None' not handled in switch"
			default:
				break;
		}
		
		sf::Vector2i nextGridPos( pos.x / Game::TileSize, pos.y / Game::TileSize );
		
		return game.IsTileEmpty( ( * map ), nextGridPos );
	}
	
	bool Npc::Movement( MovementDirection a, char b, int c )
	{
		if ( b == 'x' )
		{
			sprite.Move( c, 0 );
		}
		else
		{
			sprite.Move( 0, c );
		}
		
		return true;
	}
}
