#ifndef OBJ_NPC_H
#define OBJ_NPC_H

#include <SFML/System.hpp>

#include "obj/GridObject.h"

namespace obj
{
	class CameraController;
	
	class Npc : public GridObject
	{
		public:
			Npc( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
			enum MovementDirection
			{
				// Making Up be 0 makes the subrect thing a whole lot easier
				None = -1,
				
				Up    = 0,
				Down  = 1,
				Left  = 2,
				Right = 3
			};
			void Walk( MovementDirection theNextDir );
			void StopWalking();
		
		protected:
			MovementDirection movement, nextDir;
			float renderOffset;
			float renderOffsetSpeed;
			const sf::Vector2i frameSize;
			
			static const float RenderOffsetThreshold;
			
			bool IsDirectionEmpty( MovementDirection& dir );
			
			friend class CameraController;
	};
}

#endif // OBJ_NPC_H
