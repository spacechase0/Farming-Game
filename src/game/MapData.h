#ifndef MAPDATA_H
#define MAPDATA_H

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

#include "game/LayerData.h"

class MapData
{
	public:
		MapData();
		
		bool loadFromFile( const std::string& filename );
		bool saveToFile( const std::string& filename );
		
		void setName( const std::string& theName );
		std::string getName() const;
		
		void setIndoor( bool theIndoor );
		bool isIndoor() const;
		
		void setSize( sf::Vector2< sf::Uint16 > theSize );
		sf::Vector2< sf::Uint16 > getSize() const;
		
		void setCollision( sf::Vector2< sf::Uint16 > pos, bool col );
		bool getCollision( sf::Vector2< sf::Uint16 > pos );
		const std::vector< bool >& getCollisions() const;
		
		void setLayer( sf::Uint8 index, LayerData layer );
		void insertLayer( sf::Uint8 index, LayerData layer );
		void addLayer( LayerData layer );
		void removeLayer( sf::Uint8 index );
		const LayerData& getLayer( sf::Uint8 index ) const;
		LayerData& getLayer( sf::Uint8 index );
		sf::Uint8 getLayerCount() const;
	
	protected:
		std::string name;
		bool indoor;
		
		sf::Vector2< sf::Uint16 > size;
		std::vector< bool > collisions;
		std::vector< LayerData > layers;
};

#endif // MAPDATA_H
