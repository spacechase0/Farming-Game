#include "item/Food.h"

namespace item
{
	Food::Food( const std::string& theName, size_t theIndex, size_t thePrice )
	   : Item::Item( theName, theIndex ),
	     price( thePrice )
	{
	}
	
	Food::Type Food::GetType() const
	{
		return Type::Food;
	}
}
