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
				// Making Up be 0 makes the subrect thing a whole lot easier
				None = -1,
				
				Up    = 0,
				Down  = 1,
				Left  = 2,
				Right = 3
			} movement, nextDir;
			float renderOffset;
			static const float RenderOffsetThreshold;
			static const float RenderOffsetMultiplier;
			static const sf::Vector2i FrameSize;
	};
}

#endif // OBJ_PLAYER_H
