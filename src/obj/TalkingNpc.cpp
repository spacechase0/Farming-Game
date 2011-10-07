#include "obj/TalkingNpc.h"

#include "scenes/SceneGame.h"

namespace obj
{
	TalkingNpc::TalkingNpc( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2i theFrameSize, sf::Vector2f thePos )
	   : Npc::Npc( theGame, theMap, theTexture, theFrameSize ),
	     text{ "Hello", "World!" }
	{
		SetPosition( thePos );
	}
	
	void TalkingNpc::Talk()
	{
		game.CreateChatDialog( text );
	}
}

