#include "SceneGuiBase.h"

SceneGuiBase::SceneGuiBase( Game& theGame )
   : SceneBase::SceneBase( theGame )
{
}

void SceneGuiBase::Initialize()
{
}

void SceneGuiBase::Terminate()
{
	gui.clear();
}

void SceneGuiBase::Update( sf::RenderWindow& window )
{
	for ( auto it = gui.begin(); it != gui.end(); ++it )
	{
		( * it )->Update( window );
	}
}

void SceneGuiBase::Update( sf::RenderWindow& window, const sf::Event& event )
{
	for ( auto it = gui.begin(); it != gui.end(); ++it )
	{
		( * it )->Update( window, event );
	}
}

void SceneGuiBase::DrawGui( sf::RenderWindow& window )
{
	for ( auto it = gui.begin(); it != gui.end(); ++it )
	{
		( * it )->Draw( window );
	}
}

