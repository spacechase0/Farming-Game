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

    boost::shared_ptr< gui::TextButton > btnNew( new gui::TextButton() );
    btnNew->SetTexture( tex );
    btnNew->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
    btnNew->SetPosition( ( Game::WindowSize.x - tex.GetWidth() ) / 5, 210 );

    btnNew->SetFont( font );
    btnNew->SetCharacterSize( 24 );
    btnNew->SetString( "New Game" );
    btnNew->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );

    {
        using namespace std::placeholders;
        auto callback = std::bind( &SceneMainMenu::ButtonCallback, this, _1, _2 );
        btnNew->SetCallback( callback );
    }

    gui.push_back( btnNew );

    boost::shared_ptr< gui::TextButton > btnLoad( new gui::TextButton() );
    btnLoad->SetTexture( tex );
    btnLoad->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
    btnLoad->SetPosition( ( Game::WindowSize.x - tex.GetWidth() ) / 1.3, 210 );

    btnLoad->SetFont( font );
    btnLoad->SetCharacterSize( 24 );
    btnLoad->SetString( "Load Game" );
    btnLoad->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );

    {
        using namespace std::placeholders;
        auto callback = std::bind( &SceneMainMenu::ButtonCallback, this, _1, _2 );
        btnLoad->SetCallback( callback );
    }

    gui.push_back( btnLoad );

    boost::shared_ptr< gui::TextButton > btnOptions( new gui::TextButton() );
    btnOptions->SetTexture( tex );
    btnOptions->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
    btnOptions->SetPosition( ( Game::WindowSize.x - tex.GetWidth() ) / 5, 330 );

    btnOptions->SetFont( font );
    btnOptions->SetCharacterSize( 24 );
    btnOptions->SetString( "Options" );
    btnOptions->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );

    {
        using namespace std::placeholders;
        auto callback = std::bind( &SceneMainMenu::ButtonCallback, this, _1, _2 );
        btnOptions->SetCallback( callback );
    }

    gui.push_back( btnOptions );

    boost::shared_ptr< gui::TextButton > btnQuit( new gui::TextButton() );
    btnQuit->SetTexture( tex );
    btnQuit->SetRects( sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 0, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 1, tex.GetWidth(), tex.GetHeight() / 3 ),
                      sf::IntRect( 0, ( tex.GetHeight() / 3 ) * 2, tex.GetWidth(), tex.GetHeight() / 3 ) );
    btnQuit->SetPosition( ( Game::WindowSize.x - tex.GetWidth() ) / 1.3, 330 );

    btnQuit->SetFont( font );
    btnQuit->SetCharacterSize( 24 );
    btnQuit->SetString( "Quit" );
    btnQuit->SetColors( sf::Color::Black, sf::Color::Black, sf::Color::White );

    {
        using namespace std::placeholders;
        auto callback = std::bind( &SceneMainMenu::ButtonCallback, this, _1, _2 );
        btnQuit->SetCallback( callback );
    }

    gui.push_back( btnQuit );
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
	if ( static_cast< gui::TextButton* >( &button )->GetString() == "New Game" )
	{
		if ( type == gui::Button::Release )
		{
			game.ChangeScene( "Game" );
		}
	}
	if ( static_cast< gui::TextButton* >( &button )->GetString() == "Load Game" )
	{
		if ( type == gui::Button::Release )
		{
			game.ChangeScene( "Game" );
		}
	}
	if ( static_cast< gui::TextButton* >( &button )->GetString() == "Options" )
	{
		if ( type == gui::Button::Release )
		{
            game.ChangeScene( "Options" );
		}
	}
	if ( static_cast< gui::TextButton* >( &button )->GetString() == "Quit" )
	{
		if ( type == gui::Button::Release )
		{
		    game.window.Close();
		}
	}
}
