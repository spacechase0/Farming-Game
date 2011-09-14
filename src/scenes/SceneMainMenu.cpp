#include "scenes/SceneMainMenu.h"

#include "Game.h"

SceneMainMenu::SceneMainMenu( Game& theGame )
   : SceneGuiBase::SceneGuiBase( theGame )
{
}

void SceneMainMenu::Initialize()
{
	sf::Texture& tex = game.GetTexture( "gui/menu-button.png" );
	sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );
	
	title.SetFont( font );
	title.SetCharacterSize( 70 );
	title.SetString( "Farming Game" );
	title.SetPosition( ( Game::WindowSize.x - title.GetRect().Width ) / 2, 40 );
	
	{
		boost::shared_ptr< gui::TextButton > button( new gui::TextButton() );
		button->SetTexture( tex );
		button->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
						  sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
						  sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
		button->SetPosition( ( Game::WindowSize.x - tex.GetWidth() ) / 2, 240 );
		
		button->SetFont( font );
		button->SetString( "Play" );
		button->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );
		
		{
			using namespace std::placeholders;
			auto callback = std::bind( &SceneMainMenu::ButtonCallback, this, _1, _2 );
			button->SetCallback( callback );
		}
		
		gui.push_back( button );
	}
}

void SceneMainMenu::Terminate()
{
	SceneGuiBase::Terminate();
}
		
void SceneMainMenu::Update( sf::RenderWindow& window )
{
	SceneGuiBase::Update( window );
}

void SceneMainMenu::Update( sf::RenderWindow& window, const sf::Event& event )
{
	if ( event.Type == sf::Event::Closed )
	{
		window.Close();
	}
	
	SceneGuiBase::Update( window, event );
}

void SceneMainMenu::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );
	
	SceneGuiBase::DrawGui( window );
	window.Draw( title );
	
	window.Display();
}

void SceneMainMenu::ButtonCallback( gui::Button::EventType type, gui::Button& button )
{
	if ( static_cast< gui::TextButton* >( &button )->GetString() == "Play" )
	{
		if ( type == gui::Button::Release )
		{
			game.ChangeScene( "Game" );
		}
	}
}
