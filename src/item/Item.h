#ifndef ITEM_ITEM_H
#define ITEM_ITEM_H

#include <string>

namespace item
{
	class Item
	{
		public:
			Item( const std::string& theName, const std::string& theDesc, size_t theIndex );
			virtual ~Item() {}
			
			enum Type
			{
				// These two are the same, except different files
				Food,
				Meal,
				
				Seed,
				Tool,
				Misc
			};
			virtual Type GetType() const;
			const std::string name;
			const std::string desc;
			const size_t index;
	};
}

#endif // ITEM_ITEM_H
