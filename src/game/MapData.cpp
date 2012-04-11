#include "game/MapData.h"

MapData::MapData()
   : indoor( false ),
     size( 0, 0 )
{
}

bool MapData::loadFromFile( const std::string& filename )
{
	return false;
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
