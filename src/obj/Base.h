#ifndef OBJ_BASE_H
#define OBJ_BASE_H

#include <SFML/Graphics.hpp>

class Game;

namespace obj
{
	class Base
	{
		public:
			Base( Game& theGame ) : game( theGame ) {}
			virtual ~Base() {}
			
			virtual void Update() = 0;
			virtual void Update( sf::Event& event ) = 0;
			virtual void Draw( sf::RenderWindow& window ) = 0;
		
		protected:
			::Game& game;
	};
}

#endif // OBJ_BASE_H
