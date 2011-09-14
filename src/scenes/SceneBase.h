#ifndef SCENES_SCENEBASE_H
#define SCENES_SCENEBASE_H

#include <SFML/Graphics.hpp>

class Game;

class SceneBase
{
	public:
		SceneBase( Game& theGame ) : game( theGame ) {}
		virtual ~SceneBase() {};
		
		virtual void Initialize() = 0;
		virtual void Terminate() = 0;
		
		virtual void Update( sf::RenderWindow& window ) = 0;
		virtual void Update( sf::RenderWindow& window, const sf::Event& event ) = 0;
		virtual void Draw( sf::RenderWindow& window ) = 0;
	
	protected:
		Game& game;
};

#endif // SCENES_SCENEBASE_H
