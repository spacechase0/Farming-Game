#include "obj/DialogIngameGui.h"

#include "Game.h"

namespace obj
{
	DialogIngameGui::DialogIngameGui( SceneGame& theGame, sf::Texture& theBackgroundTexture, sf::Texture& theSlotTexture )
	   : DialogBase::DialogBase( theGame, theBackgroundTexture ),
	     slotTexture( &theSlotTexture )
	{
		SetPosition( 0, Game::WindowSize.y - backgroundTexture->GetHeight() );
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
	}
}
