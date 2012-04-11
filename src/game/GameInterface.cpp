#include "game/GameInterface.h"

#include <util/Convert.h>
#include <SFML/Graphics.hpp>

#include "game/World.h"
#include "game/MapData.h"
#include "game/objects/GameObject.h"
#include "game/objects/Player.h"
#include "game/renderers/BaseRenderer.h"
#include "game/renderers/PlayerRenderer.h"
#include "game/LayerData.h"
#include "ResourceManager.h"

void GameInterface::initialize( World& world )
{
	{
		auto raw = []( std::shared_ptr< GameObject > obj )
	               {
					return std::shared_ptr< BaseRenderer >( new PlayerRenderer( obj ) );
	               };
		
		using namespace std::placeholders;
		std::function< std::shared_ptr< BaseRenderer >( std::shared_ptr< GameObject > ) > func = std::bind( raw, _1 );
		
		rendererMapping.insert( std::make_pair( "Player", func ) );
	}
}

void GameInterface::terminate()
{
}

void GameInterface::update( const sf::Event& event, World& world )
{
}

void GameInterface::render( sf::RenderWindow& window, World& world )
{
	renderWorld( window, world );
	renderInterface( window, world );
}

void GameInterface::renderWorld( sf::RenderWindow& window, World& world )
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
	
	{
		sf::RectangleShape border;
		border.setSize( sf::Vector2f( map.getSize().x * 32 - 8, map.getSize().y * 32 - 8 ) );
		border.setOrigin( sf::Vector2f( -4, -4 ) );
		border.setFillColor( sf::Color( 0, 0, 0, 0 ) );
		border.setOutlineColor( sf::Color( 0, 0, 0, 128 ) );
		border.setOutlineThickness( 4.f );
		window.draw( border );
	}
	
	if ( rendererClearTimer.getElapsedTime() > sf::seconds( 60.f ) )
	{
		renderers.clear();
		rendererClearTimer.restart();
	}
	
	for ( auto it = world.getNpcs().begin(); it != world.getNpcs().end(); ++it )
	{
		std::shared_ptr< GameObject > obj = std::static_pointer_cast< GameObject >( * it );
		if ( renderers.find( obj.get() ) == renderers.end() )
		{
			std::shared_ptr< BaseRenderer > renderer = rendererMapping[ obj->getType() ]( obj );
			renderers.push_back( std::make_pair( obj.get(), renderer ) );
			
			renderer->render( window, world );
		}
		else
		{
			renderers[ obj.get() ]->render( window, world );
		}
	}
}

void GameInterface::renderInterface( sf::RenderWindow& window, World& world )
{
}
