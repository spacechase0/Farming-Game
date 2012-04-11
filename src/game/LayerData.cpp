#include "game/LayerData.h"

LayerData::LayerData()
   : tileset( 0 ),
     size( 0, 0 )
{
}

void LayerData::setTileset( sf::Uint16 theTileset )
{
	tileset = theTileset;
}

sf::Uint16 LayerData::getTileset() const
{
	return tileset;
}

void LayerData::setSize( sf::Vector2< sf::Uint16 > theSize )
{
	size = theSize;
	tiles.resize( size.x * size.y );
}

sf::Vector2< sf::Uint16 > LayerData::getSize() const
{
	return size;
}

void LayerData::setTile( sf::Vector2< sf::Uint8 > pos, sf::Uint8 num )
{
	std::size_t index = pos.x + pos.y * size.x;
	if ( index >= tiles.size() )
	{
		return;
	}
	
	tiles[ index ] = num;
}

sf::Uint8 LayerData::getTile( sf::Vector2< sf::Uint8 > pos )
{
	std::size_t index = pos.x + pos.y * size.x;
	if ( index >= tiles.size() )
	{
		return 0;
	}
	
	return tiles[ index ];
}

const std::vector< sf::Uint8 >& LayerData::getTiles() const
{
	return tiles;
}
