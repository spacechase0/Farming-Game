#ifndef TILELAYER_H
#define TILELAYER_H

#include <SFML/System.hpp>

#include "util/Grid.h"
#include "Tile.h"

class TileLayer
{
	public:
		TileLayer();
		TileLayer( sf::Vector2i theSize, Tile theDefaultTile );
		
		const std::vector< Tile >& operator [] ( size_t index ) const;
		std::vector< Tile >& operator [] ( size_t index );
		
		const Tile& GetTile( size_t xIndex, size_t yIndex ) const;
		Tile& GetTile( size_t xIndex, size_t yIndex );
		
		const util::Grid< Tile >& GetTiles() const;
		util::Grid< Tile >& GetTiles();
		
	private:
		sf::Vector2i size;
		Tile defaultTile;
		util::Grid< Tile > grid;
};

#endif // TILELAYER_H
