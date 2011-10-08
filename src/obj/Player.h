#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "obj/Npc.h"

namespace obj
{
	class Player : public Npc // Ok, so NPC is an inaccurate parent for this. :P
	{
		public:
			Player( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2f thePos );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
			virtual void CollidedWith( RenderObject* object );
			
			std::string GetName() const;
			
			void SetMoney( int theMoney );
			void SpendMoney( int amount );
			int GetMoney() const;
		
		protected:
			struct
			{
				bool up, down, left, right;
			} pressed;
			std::string name;
			int money;
			
			void HandleKeyRelease();
	};
}

#endif // OBJ_PLAYER_H
