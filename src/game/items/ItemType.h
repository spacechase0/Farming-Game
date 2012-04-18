#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <memory>
#include <SFML/Config.hpp>
#include <vector>

class ItemRegistry;
class ItemSlot;
class Npc;
class World;

class ItemType
{
	public:
		virtual ~ItemType();
		
		sf::Uint16 getId();
		virtual std::string getName() = 0;
		virtual int getSalePrice() = 0;
		
		virtual void onUse( World& world, std::shared_ptr< Npc > npc, ItemSlot& slot ) = 0;
	
	private:
		friend std::vector< std::shared_ptr< ItemType > > registerItems();
		sf::Uint16 id;
};

#endif // ITEMTYPE_H
