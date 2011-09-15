#include "scenes/SceneGame.h"

#include "Game.h"

SceneGame::SceneGame( Game& game )
   : SceneBase::SceneBase( game )
{
}

void SceneGame::Initialize()
{
	sf::Texture& texture = game.GetTexture( "tiles/outside.png" );
	
	sf::Vector2i layerSize = Game::WindowSize / 32;
	Tile defaultTile( texture, 1, false );
	
	layers.push_back( TileLayer( layerSize, defaultTile ) );
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
	
	window.Display();
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
