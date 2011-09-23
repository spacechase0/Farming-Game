#include "obj/Scenery.h"

namespace obj
{
	Scenery::Scenery( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2f thePos )
	   : RenderObject::RenderObject( theGame, theTexture, thePos )
	{
	}
	
	bool Scenery::CanCollide() const
	{
		return true;
	}
	
	bool Scenery::IsSolid() const
	{
		return true;
	}
}
