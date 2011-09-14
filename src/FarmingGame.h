#ifndef FARMINGGAME_H
#define FARMINGGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

#include "scenes/SceneBase.h"

class FarmingGame
{
	public:
		FarmingGame();
		~FarmingGame();
		
		int Run();
		
		typedef boost::shared_ptr< SceneBase > ScenePtr;
		typedef std::pair< std::string, ScenePtr > SceneRef;
		std::string GetCurrentScene();
		ScenePtr GetScene( const std::string& sceneName );
		
		void ChangeScene( const std::string& sceneName );
		void AddScene( const std::string& sceneName, ScenePtr scene );
		
		sf::RenderWindow window;
		
		// Without "res/"
		sf::Texture& GetTexture( const std::string& filename );
		sf::SoundBuffer& GetSoundBuffer( const std::string& filename );
		
		static const std::string WindowTitle;
		static const sf::Vector2i WindowSize;
		static const sf::Uint8 SimulationRate;
	
	private:
		typedef boost::shared_ptr< sf::Texture > TexturePtr;
		typedef boost::shared_ptr< sf::SoundBuffer > SoundBufferPtr;
		
		typedef std::map< std::string, ScenePtr > SceneMap;
		typedef std::map< std::string, TexturePtr > TextureMap;
		typedef std::map< std::string, SoundBufferPtr > SoundBufferMap;
		
		SceneMap scenes;
		std::string currentScene;
		
		TextureMap textures;
		SoundBufferMap soundBuffers;
		
		bool isRunning;
		sf::Clock simulationTimer;
};

#endif // FARMINGGAME_H
