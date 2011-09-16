#include "item/Item.h"

namespace item
{
	Item::Item( const std::string& theName, const std::string& theDesc, size_t theIndex )
	   : name( theName ),
	     desc( theDesc ),
	     index( theIndex )
	{
	}
	
	Item::Type Item::GetType() const
	{
		return Type::Misc;
	}
}


