#include "game/renderers/NpcRenderer.h"

#include <SFML/Graphics.hpp>

#include "game/objects/Npc.h"
#include "ResourceManager.h"

NpcRenderer::NpcRenderer( std::shared_ptr< GameObject > theObject )
   : BaseRenderer::BaseRenderer( theObject ),
     npc( std::dynamic_pointer_cast< Npc >( theObject ) )
{
	spr.setTexture( * ResourceManager::getTexture( "res/character/male.png" ) );
	spr.setTextureRect( sf::IntRect( 0, 0, 32, 64 ) );
	spr.setOrigin( 16, 48 );
}

void NpcRenderer::render( sf::RenderWindow& window, const World& world )
{
	sf::Uint8 mult = npc->getFacingDirection();
	spr.setTextureRect( sf::IntRect( 0, 64 * mult, 32, 64 ) );
	
	spr.setPosition( npc->getPosition().x * 32, npc->getPosition().y * 32 );
	window.draw( spr );
}
