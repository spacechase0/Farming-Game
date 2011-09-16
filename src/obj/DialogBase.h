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
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
		protected:
			sf::Texture* backgroundTexture;
			sf::Sprite sprite;
			
			std::vector< boost::shared_ptr< gui::Base > > gui;
	};
}

#endif // OBJ_DIALOGBASE_H
