#include "game/GameInterface.h"

#include <util/Convert.h>
#include <SFML/Graphics.hpp>

#include "game/World.h"
#include "game/MapData.h"
#include "game/objects/Player.h"
#include "game/LayerData.h"
#include "ResourceManager.h"

void GameInterface::initialize( World& world )
{
}

void GameInterface::terminate()
{
}

void GameInterface::update( const sf::Event& event, const World& world )
{
}

void GameInterface::render( sf::RenderWindow& window, const World& world )
{
	renderWorld( window, world );
	renderInterface( window, world );
}

void GameInterface::renderWorld( sf::RenderWindow& window, const World& world )
{
	std::shared_ptr< const Player > player = world.getPlayer();
	const MapData& map = world.getMaps()[ player->getMap() ];
	
	for ( std::size_t i = 0; i < map.getLayerCount(); ++i )
	{
		const LayerData& layer = map.getLayer( i );
		
		sf::Texture& tex = ( * ResourceManager::getTexture( "res/tilesets/" + util::toString( layer.getTileset() ) + ".png" ) );
		sf::Sprite spr( tex );
		
		auto tiles = layer.getTiles();
		for ( std::size_t i = 0; i < tiles.size(); ++i )
		{
			float x = ( i % layer.getSize().x ) * 32;
			float y = ( i / layer.getSize().x ) * 32;
			spr.setPosition( x, y );
			
			int tx = ( tiles[ i ] % 16 ) * 32;
			int ty = ( tiles[ i ] / 16 ) * 32;
			spr.setTextureRect( sf::IntRect( tx, ty, 32, 32 ) );
			
			window.draw( spr );
		}
	}
	
	sf::RectangleShape shape;
	shape.setSize( sf::Vector2f( map.getSize().x * 32 - 8, map.getSize().y * 32 - 8 ) );
	shape.setOrigin( sf::Vector2f( -4, -4 ) );
	shape.setFillColor( sf::Color( 0, 0, 0, 0 ) );
	shape.setOutlineColor( sf::Color( 0, 0, 0, 128 ) );
	shape.setOutlineThickness( 4.f );
	window.draw( shape );
}

void GameInterface::renderInterface( sf::RenderWindow& window, const World& world )
{
}
