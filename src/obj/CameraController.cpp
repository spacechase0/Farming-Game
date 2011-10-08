#include "obj/CameraController.h"

#include "scenes/SceneGame.h"
#include "obj/Player.h"
#include "Game.h"

namespace obj
{
	CameraController::CameraController( SceneGame& theGame, sf::RenderWindow& theWindow )
	   : Base::Base( theGame ),
	     window( theWindow ),
	     view( theWindow.GetView() )
	{
		view.SetViewport( sf::FloatRect( 0, 0, 1, ( Game::WindowSize.y - 64.f ) / Game::WindowSize.y ) );
		view.SetSize( view.GetSize().x, Game::WindowSize.y - 64 );
	}
	
	void CameraController::Update()
	{
	}
	
	void CameraController::Update( const sf::Event& event )
	{
	}
	
	void CameraController::Draw( sf::RenderWindow& window )
	{
		const sf::Sprite& playerSprite = game.player->sprite;
		sf::Vector2f pos = playerSprite.GetPosition();
		
		TileLayer& layer = game.maps[ game.maps.currentMap ]->layers[ 0 ];
		sf::Vector2i layerSize( layer.GetTiles().size(), layer.GetTiles()[ 0 ].size() );
		sf::Vector2i visibleTiles( Game::WindowSize.x / Game::TileSize, ( Game::WindowSize.y - 64 ) / Game::TileSize );
		sf::Vector2i halfScreen( ( visibleTiles.x / 2 ) * Game::TileSize, ( visibleTiles.y / 2 ) * Game::TileSize );
		
		if ( pos.x < halfScreen.x )
		{
			pos.x = halfScreen.x;
		}
		else if ( pos.x > ( layerSize.x * Game::TileSize ) - halfScreen.x )
		{
			pos.x = ( layerSize.x * Game::TileSize ) - halfScreen.x;
		}
		
		if ( pos.y < halfScreen.y )
		{
			pos.y = halfScreen.y;
		}
		else if ( pos.y > ( layerSize.y * Game::TileSize ) - halfScreen.y - Game::TileSize )
		{
			pos.y = ( layerSize.y * Game::TileSize ) - halfScreen.y - Game::TileSize;
		}
		
		pos.x = static_cast< int >( pos.x );
		pos.y = static_cast< int >( pos.y + ( Game::TileSize / 2 ) );
		
		view.SetCenter( pos );
		window.SetView( view );
	}
}
