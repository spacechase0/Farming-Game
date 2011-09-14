#ifndef GUI_TEXTBUTTON_H
#define GUI_TEXTBUTTON_H

#include "gui/Button.h"

namespace gui
{
	class TextButton : public Button
	{
		public:
			TextButton();
			TextButton( sf::Texture& theTexture, sf::IntRect rectIdle, sf::IntRect rectHover, sf::IntRect rectPress );
			
			void SetFont( sf::Font& theFont );
			sf::Font& GetFont() const;
			
			void SetString( const std::string& str );
			std::string GetString() const;
			
			void SetColors( sf::Color idleColor, sf::Color hoverColor, sf::Color pressColor );
			sf::Color GetIdleColor() const;
			sf::Color GetHoverColor() const;
			sf::Color GetPressColor() const;
			
			virtual void Draw( sf::RenderWindow& window );
		
		protected:
			struct
			{
				sf::Color idle;
				sf::Color hover;
				sf::Color press;
			} colors;
			sf::Text text;
			sf::Font* font;
			
			void UpdateFontColor();
			void UpdateTextPosition();
	};
}

#endif // GUI_TEXTBUTTON_H
