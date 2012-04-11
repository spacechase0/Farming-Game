#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "game/World.h"

class GameScene : public Scene
{
	public:
		GameScene( Game& theGame );
	
		virtual void initialize( SceneChangeEvent& event );
		virtual void terminate();
		
		virtual void update();
		virtual void update( const sf::Event& event );
		virtual void render( sf::RenderWindow& window );
	
	private:
		World world;
};

#endif // GAMESCENE_H
