#ifndef SCENE_H
#define SCENE_H

namespace sf
{
	class RenderWindow;
	class Event;
}
class Game;
class SceneChangeEvent;

class Scene
{
	public:
		Scene( Game& theGame );
		virtual ~Scene();
		
		virtual void initialize( SceneChangeEvent& event ) = 0;
		virtual void terminate() = 0;
		
		virtual void update() = 0;
		virtual void update( const sf::Event& event ) = 0;
		virtual void render( sf::RenderWindow& window ) = 0;
	
	protected:
		Game& game;
};

#endif // SCENE_H
