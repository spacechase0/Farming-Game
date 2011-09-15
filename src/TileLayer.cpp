#include "TileLayer.h"

TileLayer::TileLayer()
{
}

TileLayer::TileLayer( sf::Vector2i theSize, Tile theDefaultTile )
   : size( theSize ),
     defaultTile( theDefaultTile ),
     grid( size.x, std::vector< Tile >( size.y, defaultTile ) )
{
}

const std::vector< Tile >& TileLayer::operator [] ( size_t index ) const
{
	return grid[ index ];
}

std::vector< Tile >& TileLayer::operator [] ( size_t index )
{
	return grid[ index ];
}

const Tile& TileLayer::GetTile( size_t xIndex, size_t yIndex ) const
{
	return grid[ xIndex ][ yIndex ];
}

Tile& TileLayer::GetTile( size_t xIndex, size_t yIndex )
{
	return grid[ xIndex ][ yIndex ];
}

const util::Grid< Tile >& TileLayer::GetTiles() const
{
	return grid;
}

util::Grid< Tile >& TileLayer::GetTiles()
{
	return grid;
}
