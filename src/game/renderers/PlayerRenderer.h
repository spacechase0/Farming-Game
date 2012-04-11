#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include "game/renderers/BaseRenderer.h"

class PlayerRenderer : public BaseRenderer
{
	public:
		PlayerRenderer( std::shared_ptr< GameObject > theObject );
		
		virtual void render( sf::RenderWindow& window, const World& world );
};

#endif // PLAYERRENDERER_H
