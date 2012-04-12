#include "game/renderers/PlayerRenderer.h"

#include <SFML/Graphics.hpp>

#include "game/objects/Player.h"
#include "ResourceManager.h"

PlayerRenderer::PlayerRenderer( std::shared_ptr< GameObject > theObject )
   : BaseRenderer::BaseRenderer( theObject ),
     player( std::dynamic_pointer_cast< Player >( theObject ) )
{
	spr.setTexture( * ResourceManager::getTexture( "res/character/male.png" ) );
	spr.setTextureRect( sf::IntRect( 0, 0, 32, 64 ) );
	spr.setOrigin( 16, 48 );
}

void PlayerRenderer::render( sf::RenderWindow& window, const World& world )
{
	spr.setPosition( player->getPosition().x * 32, player->getPosition().y * 32 );
	window.draw( spr );
}
