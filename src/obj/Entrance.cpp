#include "obj/Entrance.h"

#include "Game.h"

namespace obj
{
	Entrance::Entrance( SceneGame& theGame, sf::Texture& tex, sf::Vector2i theGridPos, const std::string& theDest, sf::Vector2i theDestPos )
	   : RenderObject::RenderObject( theGame, tex, sf::Vector2f( theGridPos.x * 32, theGridPos.y * 32 ) ),
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
	}
	
	bool Entrance::CanCollide() const
	{
		return true;
	}
	
	sf::FloatRect Entrance::GetCollisionRect() const
	{
		return sf::FloatRect( gridPos.x * Game::TileSize, gridPos.y * Game::TileSize, Game::TileSize, Game::TileSize );
	}
}
