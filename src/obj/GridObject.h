#ifndef OBJ_GRIDOBJECT_H
#define OBJ_GRIDOBJECT_H

#include "obj/Base.h"

namespace obj
{
	class GridObject : public Base
	{
		public:
			GridObject( Game& theGame, sf::Texture& theTexture, sf::Vector2i theGridPos );
			
			void SetTexture( sf::Texture& theTexture );
			sf::Texture& GetTexture() const;
			
			void SetGridPosition( sf::Vector2i theGridPos );
			sf::Vector2i GetGridPosition();
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
		
		protected:
			sf::Sprite sprite;
			sf::Texture* texture;
			sf::Vector2i gridPos;
	};
}

#endif // OBJ_GRIDOBJECT_H
