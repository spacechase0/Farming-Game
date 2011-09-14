#include "FarmingGame.h"

#include <stdexcept>

const sf::Uint8 FarmingGame::SimulationRate = 50;
const std::string FarmingGame::WindowTitle = "Farming Game";
const sf::Vector2i FarmingGame::WindowSize( 640, 480 );

FarmingGame::FarmingGame()
{
}

FarmingGame::~FarmingGame()
{
	if ( GetCurrentScene() != "" )
	{
		scenes[ currentScene ]->Terminate();
	}
}

int FarmingGame::Run()
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
		
		// Simulate only FarmingGame::SimulationRate times a second
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

std::string FarmingGame::GetCurrentScene()
{
	if ( scenes.find( currentScene ) == scenes.end() )
	{
		return "";
	}
	
	return currentScene;
}

FarmingGame::ScenePtr FarmingGame::GetScene( const std::string& sceneName )
{
	if ( scenes.find( sceneName ) == scenes.end() )
	{
		std::cout << "Warning: Scene '" << sceneName << "' does not exist." << std::endl;
		return ScenePtr();
	}
	
	return scenes[ sceneName ];
}

void FarmingGame::ChangeScene( const std::string& sceneName )
{
	if ( scenes.find( sceneName ) == scenes.end() )
	{
		throw std::invalid_argument( "Scene '" + sceneName + "' does not exist." );
	}
	
	currentScene = sceneName;
}

void FarmingGame::AddScene( const std::string& sceneName, ScenePtr scene )
{
	if ( scenes.find( sceneName ) == scenes.end() )
	{
		throw std::invalid_argument( "Duplicate scene '" + sceneName + "'." );
	}
	
	scenes.insert( std::make_pair( sceneName, scene ) );
}

sf::Texture& FarmingGame::GetTexture( const std::string& filename )
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

sf::Font& FarmingGame::GetFont( const std::string& filename )
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

sf::SoundBuffer& FarmingGame::GetSoundBuffer( const std::string& filename )
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
