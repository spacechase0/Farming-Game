#include "item/Seed.h"

namespace item
{
	Seed::Seed( const std::string& theName, const std::string& theDesc, size_t theIndex, const std::string& theCrop )
	   : Item::Item( theName, theDesc, theIndex ),
	     crop( theCrop )
	{
	}
	
	Seed::Type Seed::GetType() const
	{
		return Type::Seed;
	}
}

