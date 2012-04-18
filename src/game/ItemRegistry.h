#ifndef ITEMREGISTRY_H
#define ITEMREGISTRY_H

#include <memory>
#include <vector>

#include "game/items/ItemType.h"

class ItemRegistry
{
	public:
		static std::shared_ptr< ItemType > getItem( sf::Uint16 id );
	
	private:
		~ItemRegistry() = delete;
		
		static std::vector< std::shared_ptr< ItemType > > types;
};

#endif // ITEMREGISTRY_H
