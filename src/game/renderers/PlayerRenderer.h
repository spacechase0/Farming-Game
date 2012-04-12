#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include <SFML/Graphics/Sprite.hpp>

#include "game/renderers/BaseRenderer.h"

class Player;

class PlayerRenderer : public BaseRenderer
{
	public:
		PlayerRenderer( std::shared_ptr< GameObject > theObject );
		
		virtual void render( sf::RenderWindow& window, const World& world );
	
	private:
		std::shared_ptr< Player > player;
		sf::Sprite spr;
};

#endif // PLAYERRENDERER_H
