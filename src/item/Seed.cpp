#include "item/Seed.h"

namespace item
{
	Seed::Seed( const std::string& theName, size_t theIndex, const std::string& theCrop )
	   : Item::Item( theName, theIndex ),
	     crop( theCrop )
	{
	}
	
	Seed::Type Seed::GetType() const
	{
		return Type::Seed;
	}
}

