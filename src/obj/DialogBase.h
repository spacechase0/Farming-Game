#ifndef OBJ_DIALOGBASE_H
#define OBJ_DIALOGBASE_H

#include "obj/Base.h"
#include "gui/Base.h"

namespace obj
{
	class DialogBase : public Base
	{
		public:
			DialogBase( SceneGame& theGame, sf::Texture& theBackgroundTexture );
			
			void SetPosition( sf::Vector2f pos );
			void SetPosition( float x, float y );
			sf::Vector2f GetPosition() const;
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
			virtual int GetDepth() const;
			
		protected:
			sf::Texture* backgroundTexture;
			sf::Sprite sprite;
			
			std::vector< boost::shared_ptr< gui::Base > > gui;
	};
}

#endif // OBJ_DIALOGBASE_H
