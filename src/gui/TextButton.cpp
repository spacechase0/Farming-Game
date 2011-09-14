#include "gui/TextButton.h"

namespace gui
{
	TextButton::TextButton()
	   : Button::Button()
	{
	}
	
	TextButton::TextButton( sf::Texture& theTexture, sf::IntRect rectIdle, sf::IntRect rectHover, sf::IntRect rectPress )
	   : Button::Button( theTexture, rectIdle, rectHover, rectPress )
	{
	}
	
	void TextButton::SetFont( sf::Font& theFont )
	{
		text.SetFont( theFont );
		font = &theFont;
	}
	
	sf::Font& TextButton::GetFont() const
	{
		return ( * font );
	}
	
	void TextButton::SetCharacterSize( unsigned int size )
	{
		text.SetCharacterSize( size );
	}
	
	unsigned int TextButton::GetCharacterSize()
	{
		return text.GetCharacterSize();
	}
	
	void TextButton::SetString( const std::string& str )
	{
		text.SetString( str );
	}
	
	std::string TextButton::GetString() const
	{
		return text.GetString();
	}
	
	void TextButton::SetColors( sf::Color idleColor, sf::Color hoverColor, sf::Color pressColor )
	{
		colors.idle = idleColor;
		colors.hover = hoverColor;
		colors.press = pressColor;
	}
	
	sf::Color TextButton::GetIdleColor() const
	{
		return colors.idle;
	}
	
	sf::Color TextButton::GetHoverColor() const
	{
		return colors.hover;
	}
	
	sf::Color TextButton::GetPressColor() const
	{
		return colors.press;
	}
	
	void TextButton::Draw( sf::RenderWindow& window )
	{
		Button::Draw( window );
		
		UpdateFontColor();
		UpdateTextPosition();
		window.Draw( text );
	}
	
	void TextButton::UpdateFontColor()
	{
		if ( state.pressed )
		{
			text.SetColor( colors.press );
		}
		else if ( state.inside )
		{
			text.SetColor( colors.hover );
		}
		else
		{
			text.SetColor( colors.idle );
		}
	}
	
	void TextButton::UpdateTextPosition()
	{
		sf::FloatRect textRect = text.GetRect();
		sf::IntRect spriteRect = sprite.GetSubRect();
		
		float offsetX = ( spriteRect.Width - textRect.Width ) / 2;
		float offsetY = ( spriteRect.Height - textRect.Height ) / 2;
		
		text.SetPosition( sprite.GetPosition() );
		text.Move( offsetX, offsetY );
	}
}
