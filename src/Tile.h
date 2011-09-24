#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
	public:
		Tile();
		Tile( sf::Texture& theTexture, sf::Uint8 theIndex );
		
		void SetTexture( sf::Texture& theTexture );
		sf::Texture& GetTexture() const;
		
		void SetIndex( sf::Uint8 theIndex );
		sf::Uint8 GetIndex() const;
	
	private:
		sf::Texture* texture;
		sf::Uint8 index;
};

#endif // TILE_H
