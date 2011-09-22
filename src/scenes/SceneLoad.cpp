#include "scenes/SceneLoad.h"

#include "Game.h"

SceneLoad::SceneLoad( Game& theGame )
   : SceneGuiBase::SceneGuiBase( theGame )
{
}

void SceneLoad::Initialize()
{
	sf::Texture& tex = game.GetTexture( "gui/menu-button.png" );
	sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );

	title.SetFont( font );
	title.SetCharacterSize( 50 );
	title.SetString( "Load Game" );
	title.SetPosition( ( Game::WindowSize.x - title.GetRect().Width ) / 2, 40 );

	CreateButton( "Back",  sf::Vector2f( ( Game::WindowSize.x - tex.GetWidth() ) / 2,   400 ), tex, font, 24 );
}

void SceneLoad::Terminate()
{
	SceneGuiBase::Terminate();
}

void SceneLoad::Update( sf::RenderWindow& window )
{
	SceneGuiBase::Update( window );
}

void SceneLoad::Update( sf::RenderWindow& window, const sf::Event& event )
{
	if ( event.Type == sf::Event::Closed )
	{
		window.Close();
	}

	SceneGuiBase::Update( window, event );
}

void SceneLoad::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );

	SceneGuiBase::DrawGui( window );
	window.Draw( title );

	window.Display();
}

void SceneLoad::CreateButton( const std::string& text, sf::Vector2f pos, sf::Texture& tex, sf::Font& font, size_t charSize )
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
        auto callback = std::bind( &SceneLoad::ButtonCallback, this, _1, _2 );
        button->SetCallback( callback );
    }

    gui.push_back( button );
}

void SceneLoad::ButtonCallback( gui::Button::EventType type, gui::Button& button )
{
    if ( type != gui::Button::Release )
	{
		return;
	}

	gui::TextButton* btn = static_cast< gui::TextButton* >( &button );

	if ( btn->GetString() == "Back" )
	{
		game.ChangeScene( "MainMenu" );
	}
}
