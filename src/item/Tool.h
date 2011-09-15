#ifndef ITEM_TOOL_H
#define ITEM_TOOL_H

#include <vector>

#include "item/Item.h"

namespace item
{
	class Tool : public Item
	{
		public:
			enum Action
			{
				Dig,
				Chop,
				Fish
			};
			
			Tool( const std::string& theName, size_t theIndex, Action theAction, float theBreakChance );
			
			virtual Type GetType() const;
			Action action;
			float breakChance;
	};
}

#endif // ITEM_TOOL_H

