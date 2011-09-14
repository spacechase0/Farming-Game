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
	
	{
		boost::shared_ptr< gui::TextButton > button( new gui::TextButton() );
		button->SetTexture( tex );
		button->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
						 sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
						 sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
		button->SetPosition( 0, 0 );
		
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
	
	window.Display();
}

void SceneMainMenu::ButtonCallback( gui::Button::EventType type, gui::Button& button )
{
	std::cout << "Button event " << type << std::endl;
}
