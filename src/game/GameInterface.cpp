#include "game/GameInterface.h"

#include <util/Convert.h>
#include <SFML/Graphics.hpp>

#include "game/World.h"
#include "game/MapData.h"
#include "game/objects/GameObject.h"
#include "game/objects/Player.h"
#include "game/renderers/BaseRenderer.h"
#include "game/renderers/NpcRenderer.h"
#include "game/LayerData.h"
#include "ResourceManager.h"

namespace
{
	std::shared_ptr< BaseRenderer > createNpcRenderer( std::shared_ptr< GameObject > obj )
	{
		return std::shared_ptr< BaseRenderer >( new NpcRenderer( obj ) );
	}
}

void GameInterface::initialize( World& world )
{
	{
		using namespace std::placeholders;
		rendererMapping.insert( std::make_pair( "Player", std::bind( &createNpcRenderer, _1 ) ) );
	}
	
	{
		sf::Texture& tex = ( * ResourceManager::getTexture( "res/gui/dial.png" ) );
		
		time.sky.setTexture( tex );
		time.sky.setTextureRect( sf::IntRect( 64, 0, 64, 64 ) );
		time.sky.setOrigin( 32, 32 );
		time.sky.setPosition( 32 + 10, 32 + 10 );
		
		time.stars.setTexture( tex );
		time.stars.setTextureRect( sf::IntRect( 128, 0, 64, 64 ) );
		time.stars.setOrigin( 32, 32 );
		time.stars.setPosition( 32 + 10, 32 + 10 );
		
		time.glow.setTexture( tex );
		time.glow.setTextureRect( sf::IntRect( 64, 32, 32, 32 ) );
		time.glow.setOrigin( 20, 20 );
		time.glow.setPosition( 32 + 10, 32 + 10 );
		
		time.moon.setTexture( tex );
		time.moon.setTextureRect( sf::IntRect( 32, 96, 16, 16 ) );
		time.moon.setOrigin( 20, 20 );
		time.moon.setPosition( 32 + 10, 32 + 10 );
		
		time.sun.setTexture( tex );
		time.sun.setTextureRect( sf::IntRect( 0, 96, 32, 32 ) );
		time.sun.setOrigin( 28, 28 );
		time.sun.setPosition( 32 + 10, 32 + 10 );
		
		time.ground.setTexture( tex );
		time.ground.setTextureRect( sf::IntRect( 128, 64, 64, 64 ) );
		time.ground.setOrigin( 32, 32 );
		time.ground.setPosition( 32 + 10, 32 + 10 );
		
		time.rim.setTexture( tex );
		time.rim.setTextureRect( sf::IntRect( 0, 0, 64, 64 ) );
		time.rim.setOrigin( 32, 32 );
		time.rim.setPosition( 32 + 10, 32 + 10 );
	}
	{
		sf::Texture& tex = ( * ResourceManager::getTexture( "res/gui/bars.png" ) );
		
		bars.back.setTexture( tex );
		bars.back.setTextureRect( sf::IntRect( 0, 0, 128, 22 ) );
		bars.back.setPosition( 640 - 128 - 10, 10 );
		
		bars.fat.setTexture( tex );
		bars.fat.setTextureRect( sf::IntRect( 0, 22, 124, 8 ) );
		bars.fat.setPosition( bars.back.getPosition().x + 2, bars.back.getPosition().y + 2 );
		
		bars.star.setTexture( tex );
		bars.star.setTextureRect( sf::IntRect( 0, 30, 124, 8 ) );
		bars.star.setPosition( bars.back.getPosition().x + 2, bars.back.getPosition().y + 2 + 8 + 2 );
	}
}

void GameInterface::terminate()
{
}

void GameInterface::update( const sf::Event& event, World& world )
{
	std::shared_ptr< Player > player = world.getPlayer();
	
	if ( event.type == sf::Event::KeyPressed )
	{
		bool movement = false;
		Direction::Direction dir;
		if ( event.key.code == sf::Keyboard::W or event.key.code == sf::Keyboard::Up )
		{
			movement = true;
			dir = Direction::Up;
		}
		else if ( event.key.code == sf::Keyboard::D or event.key.code == sf::Keyboard::Right )
		{
			movement = true;
			dir = Direction::Right;
		}
		else if ( event.key.code == sf::Keyboard::S or event.key.code == sf::Keyboard::Down )
		{
			movement = true;
			dir = Direction::Down;
		}
		else if ( event.key.code == sf::Keyboard::A or event.key.code == sf::Keyboard::Left )
		{
			movement = true;
			dir = Direction::Left;
		}
		
		if ( movement )
		{
			player->walk( dir );
		}
	}
	else if ( event.type == sf::Event::KeyReleased )
	{
		bool stopping = false;
		Direction::Direction dir;
		if ( event.key.code == sf::Keyboard::W or event.key.code == sf::Keyboard::Up )
		{
			stopping = true;
			dir = Direction::Up;
		}
		else if ( event.key.code == sf::Keyboard::D or event.key.code == sf::Keyboard::Right )
		{
			stopping = true;
			dir = Direction::Right;
		}
		else if ( event.key.code == sf::Keyboard::S or event.key.code == sf::Keyboard::Down )
		{
			stopping = true;
			dir = Direction::Down;
		}
		else if ( event.key.code == sf::Keyboard::A or event.key.code == sf::Keyboard::Left )
		{
			stopping = true;
			dir = Direction::Left;
		}
		
		if ( stopping and player->getNextWalkingDirection() == dir )
		{
			player->stop();
		}
	}
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
	{
		int mainRot = ( world.getTime() / 1440.f ) * -360 + 180;
		int bodyRot = mainRot + 45;
		time.stars.setRotation( mainRot );
		time.sky  .setRotation( mainRot );
		time.glow .setRotation( bodyRot + 180 );
		time.moon .setRotation( bodyRot + 180 );
		time.sun  .setRotation( bodyRot );
		
		window.draw( time.sky    );
		window.draw( time.stars  );
		//window.draw( time.glow   );
		window.draw( time.moon   );
		window.draw( time.sun    );
		window.draw( time.ground );
		window.draw( time.rim    );
	}
	{
		int fatWidth = ( world.getPlayer()->getFatigue() / static_cast< float >( world.getPlayer()->getFatigueMax() ) ) * 124;
		int starWidth = ( world.getPlayer()->getStarvation() / static_cast< float >( world.getPlayer()->getStarvationMax() ) ) * 124;
		
		bars.fat.setTextureRect( sf::IntRect( 0, 22, fatWidth, 8 ) );
		bars.star.setTextureRect( sf::IntRect( 0, 30, starWidth, 8 ) );
		
		window.draw( bars.back );
		window.draw( bars.fat );
		window.draw( bars.star );
	}
}
