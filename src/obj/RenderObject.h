#ifndef OBJ_RENDEROBJECT_H
#define OBJ_RENDEROBJECT_H

#include "obj/Base.h"

namespace obj
{
	class CameraController;
	
	class RenderObject : public Base
	{
		public:
			RenderObject( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2f thePos );
			
			void SetTexture( sf::Texture& theTexture, bool alignWithGrid = true );
			sf::Texture& GetTexture() const;
			
			void SetPosition( float x, float y );
			void SetPosition( sf::Vector2f thePos );
			sf::Vector2f GetPosition();
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
		
		protected:
			sf::Sprite sprite;
			sf::Texture* texture;
			
			friend class CameraController;
	};
}

#endif // OBJ_RENDEROBJECT_H