#include "game/items/ItemSlot.h"

#include "game/items/ItemType.h"
#include "game/ItemRegistry.h"

ItemSlot::ItemSlot()
   : id( 0 ),
     amount( 0 )
{
}

void ItemSlot::setItem( std::shared_ptr< ItemType > type )
{
	id = type->getId();
}

std::shared_ptr< ItemType > ItemSlot::getItem() const
{
	return ItemRegistry::getItem( id );
}

void ItemSlot::setAmount( sf::Uint8 theAmount )
{
	amount = theAmount;
}

sf::Uint8 ItemSlot::getAmount() const
{
	return amount;
}
