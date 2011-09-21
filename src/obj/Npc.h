#ifndef OBJ_NPC_H
#define OBJ_NPC_H

#include <SFML/System.hpp>

#include "obj/RenderObject.h"
#include "MapManager.h"

namespace obj
{
	class CameraController;
	
	class Npc : public RenderObject
	{
		public:
			Npc( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2i theGridPos );
			
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
			virtual void Walk( MovementDirection theMovement, float speed = 3.25 );
			
			sf::Vector2i GetGridPosition() const;
			bool IsDirectionEmpty( MovementDirection& theDir, float speed = 3.25 ) const;
		
		protected:
			MapManager::Map* map;
			const sf::Vector2i frameSize;
			
			friend class CameraController;
			
			bool Movement( MovementDirection a, char b, int c );
	};
}

#endif // OBJ_NPC_H
