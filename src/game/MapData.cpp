#include "game/MapData.h"

#include <iostream>
#include <fstream>

MapData::MapData()
   : indoor( false ),
     size( 0, 0 )
{
}

bool MapData::loadFromFile( const std::string& filename )
{
	std::fstream file( filename.c_str(), std::fstream::in | std::fstream::binary );
	if ( !file )
	{
		std::cout << "Failed to open file '" << filename << "'." << std::endl;
		return false;
	}
	
	while ( true )
	{
		char c = 0;
		file.read( &c, 1 );
		
		if ( c == 0 )
		{
			break;
		}
		
		name += c;
	}
	
	file.read( reinterpret_cast< char* >( &indoor ), 1 );
	
	file.read( reinterpret_cast< char* >( &size.x ), 2 );
	file.read( reinterpret_cast< char* >( &size.y ), 2 );
	
	collisions.resize( size.x * size.y );
	for ( sf::Uint32 i = 0; i < static_cast< sf::Uint32 >( size.x * size.y ); ++i )
	{
		bool col = false;
		file.read( reinterpret_cast< char* >( &col ), 1 );
		
		collisions[ i ] = col;
	}
	
	sf::Uint8 layerCount = 0;
	file.read( reinterpret_cast< char* >( &layerCount ), 1 );
	for ( sf::Uint8 i = 0; i < layerCount; ++i )
	{
		LayerData layer;
		layer.setSize( sf::Vector2< sf::Uint16 >( size.x, size.y ) );
		
		sf::Uint16 tileset = 0;
		file.read( reinterpret_cast< char* >( &tileset ), 2 );
		layer.setTileset( tileset );
		
		for ( sf::Uint16 ix = 0; ix < size.x; ++ix )
		{
			for ( sf::Uint16 iy = 0; iy < size.y; ++iy )
			{
				sf::Uint8 tile = 0;
				file.read( reinterpret_cast< char* >( &tileset ), 1 );
				
				layer.setTile( sf::Vector2< sf::Uint16 >( ix, iy ), tile );
			}
		}
		
		layers.push_back( layer );
	}
	
	return file.good();
}

bool MapData::saveToFile( const std::string& filename )
{
	return false;
}

void MapData::setName( const std::string& theName )
{
	name = theName;
}

std::string MapData::getName() const
{
	return name;
}

void MapData::setIndoor( bool theIndoor )
{
	indoor = theIndoor;
}

bool MapData::isIndoor() const
{
	return indoor;
}

void MapData::setSize( sf::Vector2< sf::Uint16 > theSize )
{
	size = theSize;
	collisions.resize( size.x * size.y );
	for ( auto it = layers.begin(); it != layers.end(); ++it )
	{
		it->setSize( size );
	}
}

sf::Vector2< sf::Uint16 > MapData::getSize() const
{
	return size;
}

void MapData::setCollision( sf::Vector2< sf::Uint16 > pos, bool col )
{
	std::size_t index = pos.x + pos.y * size.x;
	if ( index >= collisions.size() )
	{
		return;
	}
	
	collisions[ index ] = col;
}

bool MapData::getCollision( sf::Vector2< sf::Uint16 > pos )
{
	std::size_t index = pos.x + pos.y * size.x;
	if ( index >= collisions.size() )
	{
		return false;
	}
	
	return collisions[ index ];
}

const std::vector< bool >& MapData::getCollisions() const
{
	return collisions;
}

void MapData::setLayer( sf::Uint8 index, LayerData layer )
{
	if ( index >= layers.size() )
	{
		return;
	}
	
	layers[ index ] = layer;
}

void MapData::insertLayer( sf::Uint8 index, LayerData layer )
{
	if  ( index >= layers.size() )
	{
		addLayer( layer );
		return;
	}
	
	auto it = layers.begin() + index;
	layers.insert( it, layer );
}

void MapData::addLayer( LayerData layer )
{
	if ( layers.size() >= 0xFF )
	{
		return;
	}
	
	layers.push_back( layer );
}

void MapData::removeLayer( sf::Uint8 index )
{
	if ( index >= layers.size() )
	{
		return;
	}
	
	auto it = layers.begin() + index;
	layers.erase( it );
}

const LayerData& MapData::getLayer( sf::Uint8 index ) const
{
	return layers[ index ];
}

LayerData& MapData::getLayer( sf::Uint8 index )
{
	return layers[ index ];
}

sf::Uint8 MapData::getLayerCount() const
{
	return layers.size();
}
