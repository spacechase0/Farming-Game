#include "Game.h"

#include <stdexcept>

#include "scenes/Scenes.h"

const sf::Uint8 Game::SimulationRate = 50;
const std::string Game::WindowTitle = "Farming Game";
const sf::Vector2i Game::WindowSize( 640, 480 );

Game::Game()
{
	AddScene( "MainMenu", ScenePtr( new SceneMainMenu( * this ) ) );
	
	ChangeScene( "MainMenu" );
}

Game::~Game()
{
	if ( GetCurrentScene() != "" )
	{
		scenes[ currentScene ]->Terminate();
	}
}

int Game::Run()
{
	window.Create( sf::VideoMode( WindowSize.x, WindowSize.y ), WindowTitle, sf::Style::Titlebar | sf::Style::Close );
	scenes[ currentScene ]->Initialize();
	
	sf::Uint32 rate = 0;
	simulationTimer.Reset();
	isRunning = true;
	
	while ( isRunning )
	{
		// Current scene
		ScenePtr scene = scenes[ currentScene ];
		
		// Simulate only Game::SimulationRate times a second
		while ( rate > SimulationRate )
		{
			// Events, update loop
			sf::Event event;
			while ( window.PollEvent( event ) )
			{
				scene->Update( window, event );
			}
			scene->Update( window );
			
			rate -= ( 1000 / SimulationRate );
		}
		// Render every frame
		scene->Draw( window );
		
		rate += simulationTimer.GetElapsedTime();
		simulationTimer.Reset();
	}
	
	return 0;
}

std::string Game::GetCurrentScene()
{
	if ( scenes.find( currentScene ) == scenes.end() )
	{
		return "";
	}
	
	return currentScene;
}

Game::ScenePtr Game::GetScene( const std::string& sceneName )
{
	if ( scenes.find( sceneName ) == scenes.end() )
	{
		std::cout << "Warning: Scene '" << sceneName << "' does not exist." << std::endl;
		return ScenePtr();
	}
	
	return scenes[ sceneName ];
}

void Game::ChangeScene( const std::string& sceneName )
{
	if ( scenes.find( sceneName ) == scenes.end() )
	{
		throw std::invalid_argument( "Scene '" + sceneName + "' does not exist." );
	}
	
	if ( scenes.find( currentScene ) != scenes.end() )
	{
		scenes[ currentScene ]->Terminate();
	}
	scenes[ sceneName ]->Initialize();
	
	currentScene = sceneName;
}

void Game::AddScene( const std::string& sceneName, ScenePtr scene )
{
	if ( scenes.find( sceneName ) != scenes.end() )
	{
		throw std::invalid_argument( "Duplicate scene '" + sceneName + "'." );
	}
	
	scenes.insert( std::make_pair( sceneName, scene ) );
}

sf::Texture& Game::GetTexture( const std::string& filename )
{
	if ( textures.find( filename ) != textures.end() )
	{
		return ( * textures[ filename ] );
	}
	
	textures.insert( std::make_pair( filename, new sf::Texture() ) );
	if ( !textures[ filename ]->LoadFromFile( "res/" + filename ) )
	{
		std::cout << "Failed to load resource '" << filename << "'." << std::endl;
	}
	textures[ filename ]->SetSmooth( false );
	
	return ( * textures[ filename ] );
}

sf::Font& Game::GetFont( const std::string& filename )
{
	if ( fonts.find( filename ) != fonts.end() )
	{
		return ( * fonts[ filename ] );
	}
	
	fonts.insert( std::make_pair( filename, new sf::Font() ) );
	if ( !fonts[ filename ]->LoadFromFile( "res/" + filename ) )
	{
		std::cout << "Failed to load resource '" << filename << "'." << std::endl;
	}
	
	return ( * fonts[ filename ] );
}

sf::SoundBuffer& Game::GetSoundBuffer( const std::string& filename )
{
	if ( soundBuffers.find( filename ) != soundBuffers.end() )
	{
		return ( * soundBuffers[ filename ] );
	}
	
	soundBuffers.insert( std::make_pair( filename, new sf::SoundBuffer() ) );
	if ( !soundBuffers[ filename ]->LoadFromFile( "res/" + filename ) )
	{
		std::cout << "Failed to load resource '" << filename << "'." << std::endl;
	}
	
	return ( * soundBuffers[ filename ] );
}
