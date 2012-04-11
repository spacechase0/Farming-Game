#include "game/renderers/PlayerRenderer.h"

PlayerRenderer::PlayerRenderer( std::shared_ptr< GameObject > theObject )
   : BaseRenderer::BaseRenderer( theObject )
{
}

void PlayerRenderer::render( sf::RenderWindow& window, const World& world )
{
	//
}
