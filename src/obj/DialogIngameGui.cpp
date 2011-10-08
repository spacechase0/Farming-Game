#include "obj/DialogIngameGui.h"

#include <util/Convert.h>
#include "Game.h"
#include "scenes/SceneGame.h"
#include "obj/Player.h"

namespace obj
{
	DialogIngameGui::DialogIngameGui( SceneGame& theGame, sf::Font& theFont, sf::Texture& theBackgroundTexture, sf::Texture& theSlotTexture )
	   : DialogBase::DialogBase( theGame, theBackgroundTexture ),
	     slotTexture( &theSlotTexture ),
	     font( &theFont )
	{
		float startY = Game::WindowSize.y - backgroundTexture->GetHeight();
		SetPosition( 0, startY );
		
		slot.SetTexture( * slotTexture );
		
		name.SetFont( * font );
		name.SetCharacterSize( 20 );
		name.SetPosition( 10, startY + 6 );
		
		time.SetFont( * font );
		time.SetCharacterSize( 20 );
		time.SetPosition( 128, startY + 6 );
		
		money.SetFont( * font );
		money.SetCharacterSize( 20 );
		money.SetPosition( 256, startY + 6 );
	}

	void DialogIngameGui::Update()
	{
		DialogBase::Update();
		
		name.SetString( game.player->GetName() );
		time.SetString( game.GetTimeString() );
		money.SetString( "Money: " + util::ToString( game.player->GetMoney() ) );
	}
	
	void DialogIngameGui::Update( const sf::Event& event )
	{
		DialogBase::Update( event );
	}
	
	void DialogIngameGui::Draw( sf::RenderWindow& window )
	{
		DialogBase::Draw( window );
		
		window.Draw( name );
		window.Draw( time );
		window.Draw( money );
		
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
