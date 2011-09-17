#include "obj/RenderObject.h"

namespace obj
{
	RenderObject::RenderObject( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2f thePos )
	   : Base::Base( theGame )
	{
		SetTexture( theTexture );
		SetPosition( thePos );
	}
	
	void RenderObject::SetTexture( sf::Texture& theTexture, bool alignWithGrid )
	{
		sprite.SetTexture( theTexture );
		texture = &theTexture;
		
		if ( !alignWithGrid )
		{
			return;
		}
		
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
	
	sf::Texture& RenderObject::GetTexture() const
	{
		return ( * texture );
	}
	
	void RenderObject::SetPosition( float x, float y )
	{
		sprite.SetPosition( x, y );
	}
	
	void RenderObject::SetPosition( sf::Vector2f thePos )
	{
		sprite.SetPosition( thePos.x, thePos.y );
	}
	
	sf::Vector2f RenderObject::GetPosition()
	{
		return sprite.GetPosition();
	}
	
	void RenderObject::Update()
	{
	}
	
	void RenderObject::Update( const sf::Event& event )
	{
	}
	
	void RenderObject::Draw( sf::RenderWindow& window )
	{
		window.Draw( sprite );
	}
	
}
