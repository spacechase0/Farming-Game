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

			virtual void Update() {};
			virtual void Update( const sf::Event& event ) {};
			virtual void Draw( sf::RenderWindow& window ) {};
			
			virtual int GetDepth() const { return 0; }

		protected:
			::SceneGame& game;
	};
}

#endif // OBJ_BASE_H
