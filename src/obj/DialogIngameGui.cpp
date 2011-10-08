#include "obj/DialogIngameGui.h"

#include "Game.h"

namespace obj
{
	DialogIngameGui::DialogIngameGui( SceneGame& theGame, sf::Texture& theBackgroundTexture, sf::Texture& theSlotTexture )
	   : DialogBase::DialogBase( theGame, theBackgroundTexture ),
	     slotTexture( &theSlotTexture )
	{
		SetPosition( 0, Game::WindowSize.y - backgroundTexture->GetHeight() );
		
		slot.SetTexture( * slotTexture );
	}

	void DialogIngameGui::Update()
	{
		DialogBase::Update();
	}
	
	void DialogIngameGui::Update( const sf::Event& event )
	{
		DialogBase::Update( event );
	}
	
	void DialogIngameGui::Draw( sf::RenderWindow& window )
	{
		DialogBase::Draw( window );
		
		slot.SetPosition( Game::WindowSize.x - ( slotTexture->GetWidth() * 1 ) - ( 10 * 1 ), Game::WindowSize.y - slotTexture->GetHeight() - 10 );
		window.Draw( slot );
		slot.SetPosition( Game::WindowSize.x - ( slotTexture->GetWidth() * 2 ) - ( 10 * 2 ), Game::WindowSize.y - slotTexture->GetHeight() - 10 );
		window.Draw( slot );
		slot.SetPosition( Game::WindowSize.x - ( slotTexture->GetWidth() * 3 ) - ( 10 * 3 ), Game::WindowSize.y - slotTexture->GetHeight() - 10 );
		window.Draw( slot );
		slot.SetPosition( Game::WindowSize.x - ( slotTexture->GetWidth() * 4 ) - ( 10 * 4 ), Game::WindowSize.y - slotTexture->GetHeight() - 10 );
		window.Draw( slot );
	}
}
