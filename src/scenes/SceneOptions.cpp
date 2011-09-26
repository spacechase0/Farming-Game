#include "scenes/SceneOptions.h"

#include "Game.h"

SceneOptions::SceneOptions( Game& theGame )
   : SceneGuiBase::SceneGuiBase( theGame )
{
}

void SceneOptions::Initialize()
{
	sf::Texture& tex = game.GetTexture( "gui/menu-button.png" );
	sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );

	title.SetFont( font );
	title.SetCharacterSize( 50 );
	title.SetString( "Options" );
	title.SetPosition( ( Game::WindowSize.x - title.GetRect().Width ) / 2, 40 );

	CreateButton( "Back",  sf::Vector2f( ( Game::WindowSize.x - tex.GetWidth() ) / 2,   400 ), tex, font, 24 );
}

void SceneOptions::Terminate()
{
	SceneGuiBase::Terminate();
}

void SceneOptions::Update( sf::RenderWindow& window )
{
	SceneGuiBase::Update( window );
}

void SceneOptions::Update( sf::RenderWindow& window, const sf::Event& event )
{
	if ( event.Type == sf::Event::Closed )
	{
		window.Close();
	}

	SceneGuiBase::Update( window, event );
}

void SceneOptions::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );

	SceneGuiBase::DrawGui( window );
	window.Draw( title );

	window.Display();
}

void SceneOptions::CreateButton( const std::string& text, sf::Vector2f pos, sf::Texture& tex, sf::Font& font, size_t charSize )
{
    boost::shared_ptr< gui::TextButton > button( new gui::TextButton() );
    button->SetTexture( tex );
    button->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
    button->SetPosition( pos );

    button->SetFont( font );
    button->SetCharacterSize( charSize );
    button->SetString( text );
    button->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );

    {
        using namespace std::placeholders;
        auto callback = std::bind( &SceneOptions::ButtonCallback, this, _1, _2 );
        button->SetCallback( callback );
    }

    gui.push_back( button );
}

void SceneOptions::ButtonCallback( gui::Button::EventType type, gui::Button& button )
{
	if ( type != gui::Button::Release )
	{
		return;
	}

	gui::TextButton* btn = static_cast< gui::TextButton* >( &button );

	if ( btn->GetString() == "Back" )
	{
	    game.saveSettings();
		game.ChangeScene( "MainMenu" );
	}
}
