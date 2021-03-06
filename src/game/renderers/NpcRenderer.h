#ifndef NPCRENDEERER_H
#define NPCRENDEERER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "game/renderers/BaseRenderer.h"

class Npc;

class NpcRenderer : public BaseRenderer
{
	public:
		NpcRenderer( std::shared_ptr< GameObject > theObject );
		
		virtual void render( sf::RenderWindow& window, const World& world );
	
	private:
		std::shared_ptr< Npc > npc;
		sf::Sprite spr;
		sf::Clock animTimer;
		int animStage;
};

#endif // NPCRENDEERER_H
