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

    boost::shared_ptr< gui::TextButton > btnBack( new gui::TextButton() );
    btnBack->SetTexture( tex );
    btnBack->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
    btnBack->SetPosition( ( Game::WindowSize.x - tex.GetWidth() ) / 2, 400 );

    btnBack->SetFont( font );
    btnBack->SetCharacterSize( 24 );
    btnBack->SetString( "Back" );
    btnBack->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );

    {
        using namespace std::placeholders;
        auto callback = std::bind( &SceneOptions::ButtonCallback, this, _1, _2 );
        btnBack->SetCallback( callback );
    }

    gui.push_back( btnBack );
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

void SceneOptions::ButtonCallback( gui::Button::EventType type, gui::Button& button )
{
	if ( static_cast< gui::TextButton* >( &button )->GetString() == "Back" )
	{
		if ( type == gui::Button::Release )
		{
			game.ChangeScene( "MainMenu" );
		}
	}
}
