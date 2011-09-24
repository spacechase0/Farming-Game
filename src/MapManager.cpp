#include "MapManager.h"

#include "Game.h"
#include "util/Type.h"
#include "obj/RenderObject.h"

#define ValidateLoop(a,b,c) \
		if ( std::distance( a.begin(), b ) >= static_cast< int >( a.size() ) ) \
		{          \
			break; \
		}          \
		if ( !c ) \
		{             \
			continue; \
		}             \

void MapManager::Update( bool objects )
{
	for ( auto it = maps.begin(); objects and it != maps.end(); ++it )
	{
		ValidateLoop( maps, it, it->second.get() );
		
		auto& gameObjects = it->second->objects;
		for ( auto it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2 )
		{
			ValidateLoop( gameObjects, it2, it2->get() );
			( * it2 )->Update();
		}
	}
	for ( auto it = menuObjects.begin(); it != menuObjects.end(); ++it )
	{
		ValidateLoop( menuObjects, it, it->get() );
		( * it )->Update();
	}
}

void MapManager::Update( const sf::Event& event, bool objects )
{
	for ( auto it = maps.begin(); objects and it != maps.end(); ++it )
	{
		ValidateLoop( maps, it, it->second.get() );
		
		auto& gameObjects = it->second->objects;
		for ( auto it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2 )
		{
			ValidateLoop( gameObjects, it2, it2->get() );
			( * it2 )->Update( event );
		}
	}
	for ( auto it = menuObjects.begin(); it != menuObjects.end(); ++it )
	{
		ValidateLoop( menuObjects, it, it->get() );
		( * it )->Update( event );
	}
}

void MapManager::Draw( sf::RenderWindow& window )
{
	for ( auto it = maps[ currentMap ]->layers.begin(); it != maps[ currentMap ]->layers.end(); ++it )
	{
		TileLayer& layer = ( * it );
		DrawLayer( window, layer );
	}
	{
		auto& gameObjects = maps[ currentMap ]->objects;
		
		using namespace std::placeholders;
		auto compare = std::bind( &MapManager::CompareObjects, this, _1, _2 );
		gameObjects.sort( compare );

		for ( auto it = gameObjects.begin(); it != gameObjects.end(); ++it )
		{
			ValidateLoop( gameObjects, it, it->get() );
			( * it )->Draw( window );
		}
	}
	{
		// We want the GUI to have a static position on the screen
		sf::View oldView = window.GetView();
		sf::View newView( sf::Vector2f( Game::WindowSize.x / 2, Game::WindowSize.y / 2 ), sf::Vector2f( Game::WindowSize ) );
		window.SetView( newView );
		
		for ( auto it = menuObjects.begin(); it != menuObjects.end(); ++it )
		{
			ValidateLoop( menuObjects, it, it->get() );
			( * it )->Draw( window );
		}
		
		window.SetView( oldView );
	}
	
	CollectGarbage();
}

void MapManager::AddGarbage( ObjectList::iterator it, ObjectList* list )
{
	garbageObjects.push_back( GarbagePair( it, list ) );
}

void MapManager::AddMenuGarbage( ObjectList::iterator it )
{
	AddGarbage( it, &menuObjects );
}

void MapManager::CollectGarbage()
{
	for ( auto it = garbageObjects.begin(); it != garbageObjects.end(); ++it )
	{
		it->second->erase( it->first );
	}
	garbageObjects.clear();
}

void MapManager::DrawLayer( sf::RenderWindow& window, const TileLayer& layer ) const
{
	sf::Sprite spr;
	for ( size_t ix = 0; ix < layer.GetTiles().size(); ++ix )
	{
		for ( size_t iy = 0; iy < layer.GetTiles()[ ix ].size(); ++iy )
		{
			const Tile& tile = layer.GetTile( ix, iy );
			sf::Uint8 index = tile.GetIndex();
			spr.SetTexture( tile.GetTexture() );

			sf::Vector2i texturePos( ( index % 16 ) * Game::TileSize, ( index / 16 ) * Game::TileSize );
			spr.SetSubRect( sf::IntRect( texturePos.x, texturePos.y, Game::TileSize, Game::TileSize ) );
			spr.SetPosition( ix * 32, iy * 32 );

			window.Draw( spr );
		}
	}
}

bool MapManager::CompareObjects( const boost::shared_ptr< obj::Base >& obj1, const boost::shared_ptr< obj::Base >& obj2 )
{
	if ( !util::IsOfType< obj::RenderObject* >( obj1.get() ) or !util::IsOfType< obj::RenderObject* >( obj2.get() ) )
	{
		return false;
	}

	obj::RenderObject* firstObj = static_cast< obj::RenderObject* >( &( * obj1 ) );
	obj::RenderObject* secondObj = static_cast< obj::RenderObject* >( &( * obj2 ) );

	return ( -firstObj->GetPosition().y ) > ( -secondObj->GetPosition().y );
}
