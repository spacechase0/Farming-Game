#include "item/Tool.h"

namespace item
{
	Tool::Tool( const std::string& theName, size_t theIndex, Action theAction, float theBreakChance )
	   : Item::Item( theName, theIndex ),
	     action( theAction ),
	     breakChance( theBreakChance )
	{
	}
	
	Tool::Type Tool::GetType() const
	{
		return Type::Tool;
	}
}


