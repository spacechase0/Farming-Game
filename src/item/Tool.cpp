#include "item/Tool.h"

namespace item
{
	Tool::Tool( const std::string& theName, const std::string& theDesc, size_t theIndex, Action theAction, float theBreakChance )
	   : Item::Item( theName, theDesc, theIndex ),
	     action( theAction ),
	     breakChance( theBreakChance )
	{
	}
	
	Tool::Type Tool::GetType() const
	{
		return Type::Tool;
	}
}


