#include "game/renderers/NpcRenderer.h"

#include <SFML/Graphics.hpp>

#include "game/objects/Npc.h"
#include "ResourceManager.h"

NpcRenderer::NpcRenderer( std::shared_ptr< GameObject > theObject )
   : BaseRenderer::BaseRenderer( theObject ),
     npc( std::dynamic_pointer_cast< Npc >( theObject ) ),
     animStage( 0 )
{
	spr.setTexture( * ResourceManager::getTexture( "res/character/male.png" ) );
	spr.setTextureRect( sf::IntRect( 0, 0, 32, 64 ) );
	spr.setOrigin( 16, 48 );
}

void NpcRenderer::render( sf::RenderWindow& window, const World& world )
{
	if ( animTimer.getElapsedTime() >= sf::milliseconds( 75 ) )
	{
		animTimer.restart();
		++animStage;
	}
	if ( !npc->isWalking() or animStage >= 7 )
	{
		animStage = 0;
	}
	
	sf::Vector2f mult;
	mult.x = animStage;
	mult.y = npc->getFacingDirection();
	spr.setTextureRect( sf::IntRect( 32 * mult.x, 64 * mult.y, 32, 64 ) );
	
	spr.setPosition( npc->getPosition().x * 32, npc->getPosition().y * 32 );
	window.draw( spr );
}
