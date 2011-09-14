#include "scenes/SceneMainMenu.h"

#include "FarmingGame.h"

SceneMainMenu::SceneMainMenu( FarmingGame& theGame )
   : SceneBase( theGame ),
     buttonTex( theGame.GetTexture( "gui/menu-button.png" ) )
{
}

void SceneMainMenu::Initialize()
{
}

void SceneMainMenu::Terminate()
{
}
		
void SceneMainMenu::Update( sf::RenderWindow& window )
{
}

void SceneMainMenu::Update( sf::RenderWindow& window, const sf::Event& event )
{
}

void SceneMainMenu::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::White );
	
	sf::Sprite spr;
	spr.SetTexture( buttonTex );
	spr.SetSubRect( sf::IntRect( 0, 0, buttonTex.GetWidth(), buttonTex.GetHeight() / 3 ) );
	window.Draw( spr );
	
	window.Display();
}
