#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile( sf::Texture& theTexture, sf::Uint8 theIndex, bool theCollision )
   : texture( &theTexture ),
     index( theIndex ),
     collision( theCollision )
{
}

void Tile::SetTexture( sf::Texture& theTexture )
{
	texture = &theTexture;
}

sf::Texture& Tile::GetTexture() const
{
	return ( * texture );
}

void Tile::SetIndex( sf::Uint8 theIndex )
{
	index = theIndex;
}

sf::Uint8 Tile::GetIndex() const
{
	return index;
}

void Tile::SetCollision( bool theCollision )
{
	collision = theCollision;
}

bool Tile::GetCollision() const
{
	return collision;
}

