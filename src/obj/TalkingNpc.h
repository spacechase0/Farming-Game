#ifndef OBJ_TALKINGNPC_H
#define OBJ_TALKINGNPC_H

#include <SFML/System.hpp>

#include "obj/Npc.h"
#include "MapManager.h"

namespace obj
{
	class TalkingNpc : public Npc
	{
		public:
			TalkingNpc( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2i theFrameSize, sf::Vector2f thePos );
			
			std::vector< std::string > text;
			virtual void Talk();
	};
}

#endif // OBJ_TALKINGNPC_H

