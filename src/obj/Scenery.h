#ifndef OBJ_SCENERY_H
#define OBJ_SCENERY_H

#include "obj/RenderObject.h"

namespace obj
{
	class Scenery : public RenderObject
	{
		public:
			Scenery( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2f thePos );
			
			virtual bool CanCollide() const;
			virtual bool IsSolid() const;
	};
}

#endif // OBJ_SCENERY_H
