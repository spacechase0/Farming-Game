#include "scenes/SceneGame.h"

#include <typeinfo>

#include "Game.h"
#include "obj/Objects.h"

SceneGame::SceneGame( Game& game )
   : SceneBase::SceneBase( game )
{
}

void SceneGame::Initialize()
{
	CreateTestLayer();
	CreateTestObject();
}

void SceneGame::Terminate()
{
}

void SceneGame::Update( sf::RenderWindow& window )
{
}

void SceneGame::Update( sf::RenderWindow& window, const sf::Event& event )
{
	if ( event.Type == sf::Event::Closed )
	{
		window.Close();
	}
}

void SceneGame::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );
	
	for ( auto it = layers.begin(); it != layers.end(); ++it )
	{
		TileLayer& layer = ( * it );
		DrawLayer( window, layer );
	}
	{
		using namespace std::placeholders;
		auto compare = std::bind( &SceneGame::CompareObjects, this, _1, _2 );
		objects.sort( compare );
	}
	for ( auto it = objects.begin(); it != objects.end(); ++it )
	{
		( * it )->Draw( window );
	}
	
	window.Display();
}

void SceneGame::CreateTestLayer()
{
	sf::Texture& texture = game.GetTexture( "tiles/outside.png" );
	
	sf::Vector2i layerSize = Game::WindowSize / 32;
	Tile grassTile( texture, 1, false );
	Tile dirtTile( texture, 0, true );
	Tile sandTile( texture, 2, true );
	Tile cropTile( texture, 3, false );
	
	layers.push_back( TileLayer( layerSize, grassTile ) );
	TileLayer& layer = layers[ 0 ];
	for ( size_t ix = 0; ix < layer.GetTiles().size(); ++ix )
	{
		for ( size_t iy = 0; iy < layer.GetTiles()[ ix ].size(); ++iy )
		{
			if ( ix == 0 or ix == layer.GetTiles().size() - 1 )
			{
				layer[ ix ][ iy ] = sandTile;
			}
			else if ( iy == 0 or iy == layer.GetTiles()[ ix ].size() - 1 )
			{
				layer[ ix ][ iy ] = dirtTile;
			}
			else if ( ix >= 8 and ix <= 10 and iy >= 8 and iy <= 10 )
			{
				layer[ ix ][ iy ] = cropTile;
			}
		}
	}
}

void SceneGame::CreateTestObject()
{
	sf::Texture& texture = game.GetTexture( "characters/player-idle.png" );
	objects.push_back( boost::shared_ptr< obj::Base >( new obj::GridObject( game, texture, sf::Vector2i( 5, 5 ) ) ) );
	objects.push_back( boost::shared_ptr< obj::Base >( new obj::GridObject( game, texture, sf::Vector2i( 5, 4 ) ) ) );
}

void SceneGame::DrawLayer( sf::RenderWindow& window, const TileLayer& layer ) const
{
	sf::Texture& texture = game.GetTexture( "tiles/outside.png" );
	sf::Sprite spr( texture );
	
	for ( size_t ix = 0; ix < layer.GetTiles().size(); ++ix )
	{
		for ( size_t iy = 0; iy < layer.GetTiles()[ ix ].size(); ++iy )
		{
			const Tile& tile = layer.GetTile( ix, iy );
			sf::Uint8 index = tile.GetIndex();
			
			sf::Vector2i texturePos( ( index % 16 ) * Game::TileSize, ( index / 16 ) * Game::TileSize );
			spr.SetSubRect( sf::IntRect( texturePos.x, texturePos.y, Game::TileSize, Game::TileSize ) );
			spr.SetPosition( ix * 32, iy * 32 );
			
			window.Draw( spr );
		}
	}
}

bool SceneGame::CompareObjects( const boost::shared_ptr< obj::Base >& obj1, const boost::shared_ptr< obj::Base >& obj2 )
{
	if ( typeid( * obj1 ) != typeid( obj::GridObject ) or typeid( * obj2 ) != typeid( obj::GridObject ) )
	{
		return false;
	}
	
	obj::GridObject* firstObj = static_cast< obj::GridObject* >( &( * obj1 ) );
	obj::GridObject* secondObj = static_cast< obj::GridObject* >( &( * obj2 ) );
	
	return ( -firstObj->GetGridPosition().y ) > ( -secondObj->GetGridPosition().y );
}
