#include "scenes/SceneGame.h"

#include <typeinfo>
#include <fstream>
#include <algorithm>

#include "Game.h"
#include "obj/Objects.h"
#include <xml/Xml.h>
#include "util/Convert.h"
#include "MapLoader.h"
#include "util/Type.h"

SceneGame::SceneGame( Game& game )
   : SceneBase::SceneBase( game )
{
}

void SceneGame::Initialize()
{
	game.window.EnableKeyRepeat( false );
	
	LoadItems( "food.xml" );
	LoadItems( "seeds.xml" );
	LoadItems( "tools.xml" );
	LoadItems( "misc.xml" );

	LoadMap( "testing" );
	LoadMap( "testing2" );
	LoadMap( "house" );
	maps.currentMap = "testing";
	
	if ( maps.maps.size() > 0 )
	{
		CreatePlayer();

		cameraController = new obj::CameraController( ( * this ), game.window );
		
		sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );
		sf::Texture& back = game.GetTexture( "dialogs/ingame-bottom.png" );
		sf::Texture& slot = game.GetTexture( "gui/slot.png" );
		ingameGui = new obj::DialogIngameGui( ( * this ), font, back, slot );
		maps.menuObjects.push_back( boost::shared_ptr< obj::Base >( ingameGui ) );
		
		debug = new obj::Debug( * this );
		maps.menuObjects.push_back( boost::shared_ptr< obj::Base >( debug ) );
		
		obj::TimeDisplay* timeDisplay = new obj::TimeDisplay( * this );
		maps.menuObjects.push_back( boost::shared_ptr< obj::Base >( timeDisplay ) );
		
		sf::Texture& rain = game.GetTexture( "misc/rain.png" );
		obj::WeatherDisplay* weatherDisplay = new obj::WeatherDisplay( ( * this ), rain );
		maps.menuObjects.push_back( boost::shared_ptr< obj::Base >( weatherDisplay ) );

		simulateWorld = true;
		
		time = 7500;
		RandomizeWeather();
	}
}

void SceneGame::Terminate()
{
	maps = MapManager();
	itemDefs.clear();

	player = NULL;
	cameraController = NULL;
}

void SceneGame::Update( sf::RenderWindow& window )
{
	if ( simulateWorld )
	{
		++time;
		if ( time >= 30000 )
		{
			time -= 30000;
			RandomizeWeather();
		}
		
		maps.Update();
	}
	else
	{
		maps.Update( false );
	}
}

void SceneGame::Update( sf::RenderWindow& window, const sf::Event& event )
{
	if ( event.Type == sf::Event::Closed )
	{
		window.Close();
	}

	if ( event.Type == sf::Event::KeyPressed )
	{
		if( event.Key.Code == sf::Keyboard::Escape )
		{
			game.ChangeScene( "MainMenu" );
		}
	}

	if ( simulateWorld )
	{
		maps.Update( event );
	}
	else
	{
		maps.Update( event, false );
	}
}

void SceneGame::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );

	cameraController->Draw( window );
	maps.Draw( window );
	
	{
		sf::View oldView = window.GetView();
		sf::View newView = window.GetDefaultView();
		window.SetView( newView );
		
		window.SetView( oldView );
	}

	window.Display();

	maps.CollectGarbage();
}


bool SceneGame::IsTileEmpty( MapManager::Map& map, int x, int y )
{
	for ( auto it = map.layers.begin(); it != map.layers.end(); ++it )
	{
		if ( x < 0 or static_cast< unsigned int >( x ) >= it->GetTiles().size() or
			 y < 0 or static_cast< unsigned int >( y ) >= it->GetTiles()[ x ].size() )
		{
			continue;
		}
		
		if ( it->GetTiles()[ x ][ y ].GetCollision() )
		{
			return false;
		}
	}

	return true;
}

bool SceneGame::IsTileEmpty( MapManager::Map& map, sf::Vector2i pos )
{
	return IsTileEmpty( map, pos.x, pos.y );
}

sf::Uint16 SceneGame::GetTime() const
{
	return time;
}

std::string SceneGame::GetTimeString() const
{
	sf::Uint16 hour = time / 1250;
	sf::Uint16 minute = ( static_cast< sf::Uint16 >( ( 60.f / 1250 ) * ( time % 1250 ) ) / 10 ) * 10;
	std::string ampm = ( time < 15000 ) ? "AM" : "PM";
	
	std::stringstream ss;
	ss << hour << ":";
	ss.width( 2 );
	ss.fill( '0' );
	ss << minute;
	ss.width( 0 );
	ss << " " << ampm;
	
	return ss.str();
}

SceneGame::WeatherType SceneGame::GetWeather() const
{
	return weather;
}

void SceneGame::CreateChatDialog( const std::vector< std::string >& messages )
{
	sf::Texture& background = game.GetTexture( "dialogs/chat-base.png" );
	sf::Texture& button = game.GetTexture( "dialogs/chat-button.png" );
	sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );

	obj::Base* chat = new obj::DialogChat( ( * this ), background, button, font, messages );
	maps.menuObjects.push_back( boost::shared_ptr< obj::Base >( chat ) );

	simulateWorld = false;
}

void SceneGame::RandomizeWeather()
{
	int random = rand() % 100;
	if ( random < 5 )
	{
		weather = Rain;
	}
	else
	{
		weather = None;
	}
}

void SceneGame::LoadMap( const std::string& mapName )
{
	maps.maps.insert( std::make_pair( mapName, MapManager::MapPtr( new MapManager::Map ) ) );
	MapManager::Map& map = ( * maps[ mapName ] );

	MapLoader loader( game, ( * this ), map );
	if ( !loader.LoadMap( mapName ) )
	{
		std::vector< std::string > str;
		str.push_back( "Map '" + mapName + "' failed to load." );
		CreateChatDialog( str );
		maps.maps.erase( maps.maps.find( mapName ) );
	}
}

void SceneGame::CreatePlayer()
{
	sf::Texture& texture = game.GetTexture( "characters/player.png" );
	player = new obj::Player( ( * this ), ( * maps[ maps.currentMap ] ), texture, sf::Vector2f( 13 * Game::TileSize, 5 * Game::TileSize ) );

	maps[ maps.currentMap ]->objects.push_back( boost::shared_ptr< obj::Base >( player ) );
}

#include "scenes/SceneGame/LoadItems.inl"
