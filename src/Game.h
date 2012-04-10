#ifndef GAME_H
#define GAME_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

#include "SceneChangeEvent.h"

class Scene;

class Game
{
	public:
		Game();
		
		void run();
		void close();
		
		void changeScenes( const std::string& name, SceneChangeEvent event = SceneChangeEvent() );
		std::shared_ptr< Scene > getScene( const std::string& name );
		
		static const int UPDATE_RATE;
		static const int RENDER_RATE;
	
	private:
		sf::RenderWindow window;
		bool isRunning;
		
		void initialize();
		void terminate();
		
		std::map< std::string, std::shared_ptr< Scene > > scenes;
		std::string currentScene;
		std::string nextScene;
		SceneChangeEvent changeEvent;
		
		void addScene( const std::string& name, std::shared_ptr< Scene > scene );
};

#endif // GAME_H
