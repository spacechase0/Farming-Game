#ifndef ITEMSLOT_H
#define ITEMSLOT_H

#include <memory>
#include <SFML/Config.hpp>

class ItemType;

class ItemSlot
{
	public:
		ItemSlot();
		
		void setItem( std::shared_ptr< ItemType > type );
		std::shared_ptr< ItemType > getItem() const;
		
		void setAmount( sf::Uint8 theAmount );
		sf::Uint8 getAmount() const;
	
	private:
		sf::Uint16 id;
		sf::Uint8 amount;
};

#endif // ITEMSLOT_H
