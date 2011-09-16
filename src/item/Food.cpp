#include "item/Food.h"

namespace item
{
	Food::Food( const std::string& theName, const std::string& theDesc, size_t theIndex, size_t thePrice )
	   : Item::Item( theName, theDesc, theIndex ),
	     price( thePrice )
	{
	}
	
	Food::Type Food::GetType() const
	{
		return Type::Food;
	}
}
