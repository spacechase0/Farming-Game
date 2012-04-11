#ifndef LAYERDATA_H
#define LAYERDATA_H

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class LayerData
{
	public:
		LayerData();
		
		void setTileset( sf::Uint16 theTileset );
		sf::Uint16 getTileset() const;
		
		void setSize( sf::Vector2< sf::Uint16 > theSize );
		sf::Vector2< sf::Uint16 > getSize() const;
		
		void setTile( sf::Vector2< sf::Uint16 > pos, sf::Uint8 num );
		sf::Uint8 getTile( sf::Vector2< sf::Uint16 > pos );
		const std::vector< sf::Uint8 >& getTiles() const;
	
	private:
		sf::Uint16 tileset;
		sf::Vector2< sf::Uint16 > size;
		std::vector< sf::Uint8 > tiles;
};

#endif // LAYERDATA_H
