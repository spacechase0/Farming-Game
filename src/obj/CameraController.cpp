#include "obj/CameraController.h"

#include "scenes/SceneGame.h"
#include "obj/Player.h"

namespace obj
{
	CameraController::CameraController( SceneGame& theGame, sf::RenderWindow& theWindow )
	   : Base::Base( theGame ),
	     window( theWindow ),
	     view( theWindow.GetView() )
	{
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
		float renderOffset = game.player->renderOffset;
		
		sf::Vector2f pos = playerSprite.GetPosition();
		switch ( game.player->movement )
		{
			case Npc::Up:    pos.y += -renderOffset; break;
			case Npc::Down:  pos.y += renderOffset;  break;
			case Npc::Left:  pos.x += -renderOffset; break;
			case Npc::Right: pos.x += renderOffset;  break;
			default: break;
		}
		
		sf::Vector2i layerSize( game.layers[ 0 ].GetTiles().size(), game.layers[ 0 ].GetTiles()[ 0 ].size() );
		sf::Vector2i visibleTiles( Game::WindowSize.x / Game::TileSize, Game::WindowSize.y / Game::TileSize );
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
		std::cout << pos.y << std::endl;
		
		pos.x = static_cast< int >( pos.x );
		pos.y = static_cast< int >( pos.y + ( Game::TileSize / 2 ) );
		
		view.SetCenter( pos );
		window.SetView( view );
	}
}
