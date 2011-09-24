#include "obj/Entrance.h"

#include "Game.h"
#include "util/Type.h"
#include "obj/Npc.h"
#include "scenes/SceneGame.h"

namespace obj
{
	Entrance::Entrance( SceneGame& theGame, sf::Texture& tex, sf::Vector2i theGridPos, const std::string& theDest, sf::Vector2i theDestPos )
	   : RenderObject::RenderObject( theGame, tex, sf::Vector2f( theGridPos.x * Game::TileSize, theGridPos.y * Game::TileSize ) ),
	     dest( theDest ),
	     destPos( theDestPos )
	{
	}
	
	void Entrance::Update()
	{
	}
	
	void Entrance::Update( const sf::Event& event )
	{
	}
	
	void Entrance::Draw( sf::RenderWindow& window )
	{
		RenderObject::Draw( window );
	}
	
	bool Entrance::CanCollide() const
	{
		return true;
	}
	
	bool Entrance::IsSolid() const
	{
		return true;
	}
	
	sf::FloatRect Entrance::GetCollisionRect() const
	{
		return sf::FloatRect( sprite.GetPosition().x, sprite.GetPosition().y, Game::TileSize, Game::TileSize );
	}
	
	void Entrance::CollidedWith( RenderObject* object )
	{
		if ( !util::IsOfType< Npc* >( object ) )
		{
			return;
		}
		
		Npc* npc = static_cast< Npc* >( object );
		npc->SetMap( * game.maps[ dest ] );
		npc->SetPosition( destPos.x * Game::TileSize, destPos.y * Game::TileSize );
	}
	
	std::string Entrance::GetDestination() const
	{
		return dest;
	}
}
