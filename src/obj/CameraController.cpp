#include "obj/CameraController.h"

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
		pos.x = static_cast< int >( pos.x );
		pos.y = static_cast< int >( pos.y );
		view.SetCenter( pos );
		window.SetView( view );
	}
}
