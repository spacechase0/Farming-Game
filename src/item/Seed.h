#ifndef ITEM_SEED_H
#define ITEM_SEED_H

#include <vector>

#include "item/Item.h"

namespace item
{
	class Seed : public Item
	{
		public:
			Seed( const std::string& theName, const std::string& theDesc, size_t theIndex, const std::string& theCrop );
		
			virtual Type GetType() const;
			std::string crop;
	};
}

#endif // ITEM_SEED_H
