#ifndef OBJ_ENTRANCE_H
#define OBJ_ENTRANCE_H

#include <SFML/System.hpp>

#include "obj/RenderObject.h"

namespace obj
{
	class Entrance : public RenderObject
	{
		public:
			Entrance( SceneGame& theGame, sf::Texture& tex, sf::Vector2i theGridPos, const std::string& theDest, sf::Vector2i theDestPos );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
			virtual bool CanCollide() const;
			virtual sf::FloatRect GetCollisionRect() const;
		
		protected:
			sf::Vector2i gridPos;
			std::string dest;
			sf::Vector2i destPos;
	};
}

#endif // OBJ_ENTRANCE_H

