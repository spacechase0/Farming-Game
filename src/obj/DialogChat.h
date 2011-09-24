#ifndef OBJ_DIALOGCHAT_H
#define OBJ_DIALOGCHAT_H

#include "obj/DialogBase.h"

namespace obj
{
	class DialogChat : public DialogBase
	{
		public:
			DialogChat( SceneGame& theGame, sf::Texture& theBackgroundTexture, sf::Texture& theButtonTexture, sf::Font& theFont, const std::vector< std::string >& theText );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
			
			void CloseDialog();
		
		protected:
			sf::Font* displayFont;
			sf::Text display;
			
			sf::Texture* buttonTexture;
			sf::Sprite button;
			
			std::vector< std::string > text;
			size_t currentText;
			bool justMade;
	};
}

#endif // OBJ_DIALOGCHAT_H
