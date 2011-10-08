#ifndef OBJ_DIALOGINGAMEGUI_H
#define OBJ_DIALOGINGAMEGUI_H

#include "obj/DialogBase.h"

namespace obj
{
	class DialogIngameGui : public DialogBase
	{
		public:
			DialogIngameGui( SceneGame& theGame, sf::Texture& theBackgroundTexture, sf::Texture& theSlotTex );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
		protected:
			sf::Texture* slotTexture;
			sf::Sprite slot;
	};
}

#endif // OBJ_DIALOGINGAMEGUI_H

