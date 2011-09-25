#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
	public:
		Tile();
		Tile( sf::Texture& theTexture, sf::Uint8 theIndex, bool theCollision );
		
		void SetTexture( sf::Texture& theTexture );
		sf::Texture& GetTexture() const;
		
		void SetIndex( sf::Uint8 theIndex );
		sf::Uint8 GetIndex() const;
		
		void SetCollision( bool theCollision );
		bool GetCollision() const;
	
	private:
		sf::Texture* texture;
		sf::Uint8 index;
		bool collision;
};

#endif // TILE_H
