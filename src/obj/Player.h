#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "obj/Npc.h"

namespace obj
{
	class Player : public Npc // Ok, so NPC is an inaccurate parent for this. :P
	{
		public:
			Player( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
		
		protected:
			// Coming... Eventually
	};
}

#endif // OBJ_PLAYER_H
