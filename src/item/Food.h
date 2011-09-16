#ifndef ITEM_FOOD_H
#define ITEM_FOOD_H

#include "item/Item.h"

namespace item
{
	class Food : public Item
	{
		public:
			Food( const std::string& theName, const std::string& theDesc, size_t theIndex, size_t thePrice );
			
			virtual Type GetType() const;
			size_t price;
	};
}

#endif // ITEM_FOOD_H
