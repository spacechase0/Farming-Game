#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

#include "gui/Base.h"

namespace gui
{
	class Button : public Base
	{
		public:
			enum EventType
			{
				Enter,
				Exit,
				Press,
				Release
			};
			typedef std::function< void( EventType, Button& ) > Callback;
			
			Button();
			Button( sf::Texture& theTexture, sf::IntRect rectIdle, sf::IntRect rectHover, sf::IntRect rectPress );
			
			bool IsPressed() const;
			bool IsInside() const;
			
			void SetCallback( const Callback& theCallback );
			Callback GetCallback() const;
			
			void SetRects( sf::IntRect rectIdle, sf::IntRect rectHover, sf::IntRect rectPress );
			sf::IntRect GetIdleRect() const;
			sf::IntRect GetHoverRect() const;
			sf::IntRect GetPressRect() const;
			
			void SetPosition( float x, float y );
			void SetPosition( sf::Vector2f thePos );
			sf::Vector2f GetPosition() const;
			
			void SetTexture( sf::Texture& theTexture );
			sf::Texture& GetTexture() const;
			
			virtual void Update( sf::RenderWindow& window );
			virtual void Update( sf::RenderWindow& window, const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
		
		private:
			Callback callback;
			struct
			{
				sf::IntRect idle;
				sf::IntRect hover;
				sf::IntRect press;
			} rects;
			struct
			{
				bool pressed;
				bool inside;
			} state;
			
			sf::Sprite sprite;
			sf::Texture* texture;
			
			sf::Vector2i mousePos;
			
			void UpdateSpriteRect();
	};
}

#endif // GUI_BUTTON_H
