#include "scenes/SceneGame.h"

#include "Game.h"

SceneGame::SceneGame( Game& game )
   : SceneBase::SceneBase( game )
{
}

void SceneGame::Initialize()
{
}

void SceneGame::Terminate()
{
}

void SceneGame::Update( sf::RenderWindow& window )
{
}

void SceneGame::Update( sf::RenderWindow& window, const sf::Event& event )
{
}

void SceneGame::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );
	
	sf::Texture& tex = game.GetTexture( "tiles/grass.png" );
	sf::Sprite spr( tex );
	window.Draw( spr );
	
	window.Display();
}
