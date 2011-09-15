#include "item/Item.h"

namespace item
{
	Item::Item( const std::string& theName, size_t theIndex )
	   : name( theName ),
	     index( theIndex )
	{
	}
	
	Item::Type Item::GetType() const
	{
		return Type::Misc;
	}
}


