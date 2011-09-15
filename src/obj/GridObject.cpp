#include "obj/GridObject.h"

#include "Game.h"

namespace obj
{
	GridObject::GridObject( Game& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos )
	   : Base::Base( theGame )
	{
		SetTexture( theTexture );
		SetGridPosition( theGridPos );
	}
	
	void GridObject::SetTexture( sf::Texture& theTexture )
	{
		sprite.SetTexture( theTexture );
		texture = &theTexture;
		
		if ( ( texture->GetWidth() % 64 ) % 2 )
		{
			// We can center it nicely if it takes an odd number of tiles wide
			sprite.SetOrigin( ( texture->GetWidth() / 2 ) - ( Game::TileSize / 2 ), texture->GetHeight() - Game::TileSize );
		}
		else
		{
			sprite.SetOrigin( 0, texture->GetHeight() - Game::TileSize );
		}
	}
	
	sf::Texture& GridObject::GetTexture() const
	{
		return ( * texture );
	}
	
	void GridObject::SetGridPosition( sf::Vector2i theGridPos )
	{
		sprite.SetPosition( theGridPos.x * Game::TileSize, theGridPos.y * Game::TileSize );
		gridPos = theGridPos;
	}
	
	sf::Vector2i GridObject::GetGridPosition()
	{
		return gridPos;
	}
	
	void GridObject::Update()
	{
	}
	
	void GridObject::Update( const sf::Event& event )
	{
	}
	
	void GridObject::Draw( sf::RenderWindow& window )
	{
		window.Draw( sprite );
	}
	
}
