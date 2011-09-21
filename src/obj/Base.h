#ifndef OBJ_BASE_H
#define OBJ_BASE_H

#include <SFML/Graphics.hpp>

class SceneGame;

namespace obj
{
	class Base
	{
		public:
			Base( SceneGame& theGame ) : game( theGame ) {}
			virtual ~Base() {}
			
			virtual void Update() = 0;
			virtual void Update( const sf::Event& event ) = 0;
			virtual void Draw( sf::RenderWindow& window ) = 0;
		
		protected:
			::SceneGame& game;
	};
}

#endif // OBJ_BASE_H
