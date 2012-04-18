#include "game/ItemRegistry.h"

#include <cmath>
#include <iostream>

std::vector< std::shared_ptr< ItemType > > registerItems()
{
	std::vector< std::shared_ptr< ItemType > > types;
	types.reserve( std::pow( 2, 16 ) ); // Max amount of itmes
	
	// Register items here
	
	for ( sf::Uint16 i = 0; i < types.size(); ++i )
	{
		types[ i ]->id = i;
	}
	
	return types;
}

std::vector< std::shared_ptr< ItemType > > ItemRegistry::types = registerItems();

std::shared_ptr< ItemType > ItemRegistry::getItem( sf::Uint16 id )
{
	return types[ id ];
}
