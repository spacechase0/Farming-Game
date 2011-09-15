#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include <SFML/System.hpp>

#include "obj/GridObject.h"

namespace obj
{
	class Player : public GridObject
	{
		public:
			Player( Game& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
		
		private:
			enum Movement
			{
				None,
				
				Up,
				Down,
				Left,
				Right
			} movement, nextDir;
			float renderOffset;
			static const float RenderOffsetThreshold;
			static const float RenderOffsetMultiplier;
	};
}

#endif // OBJ_PLAYER_H
