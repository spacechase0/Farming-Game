#include "gui/Button.h"

namespace gui
{
	Button::Button()
	{
	}
	
	Button::Button( sf::Texture& theTexture, sf::IntRect rectIdle, sf::IntRect rectHover, sf::IntRect rectPress )
	   : sprite( theTexture ), texture( &theTexture )
	{
		state.pressed = false;
		state.inside = false;
		SetRects( rectIdle, rectHover, rectPress );
	}
	
	bool Button::IsPressed() const
	{
		return state.pressed;
	}
	
	bool Button::IsInside() const
	{
		return state.inside;
	}
	
	void Button::SetCallback( const Callback& theCallback )
	{
		callback = theCallback;
	}
	
	Button::Callback Button::GetCallback() const
	{
		return callback;
	}
	
	void Button::SetRects( sf::IntRect rectIdle, sf::IntRect rectHover, sf::IntRect rectPress )
	{
		rects.idle = rectIdle;
		rects.hover = rectHover;
		rects.press = rectPress;
	}
	
	sf::IntRect Button::GetIdleRect() const
	{
		return rects.idle;
	}
	
	sf::IntRect Button::GetHoverRect() const
	{
		return rects.hover;
	}
	
	sf::IntRect Button::GetPressRect() const
	{
		return rects.press;
	}
	
	void Button::SetPosition( float x, float y )
	{
		sprite.SetPosition( x, y );
	}
	
	void Button::SetPosition( sf::Vector2f thePos )
	{
		sprite.SetPosition( thePos );
	}
	
	sf::Vector2f Button::GetPosition() const
	{
		return sprite.GetPosition();
	}
	
	void Button::SetTexture( sf::Texture& theTexture )
	{
		sprite.SetTexture( theTexture );
		texture = &theTexture;
	}
	
	 sf::Texture& Button::GetTexture() const
	{
		return ( * texture );
	}
	
	void Button::Update()
	{
		UpdateSpriteRect();
	}
	
	void Button::Update( const sf::Event& event )
	{
		// Convenience variables
		sf::IntRect spriteRect( sprite.GetPosition().x, sprite.GetPosition().y, sprite.GetSubRect().Width, sprite.GetSubRect().Height );
		bool previousInside = state.inside;
		bool previousPress = state.pressed;
		
		// Processing
		if ( event.Type == sf::Event::MouseMoved )
		{
			mousePos = sf::Vector2i( event.MouseMove.X, event.MouseMove.Y );
			state.inside = spriteRect.Contains( mousePos );
			state.pressed = ( state.inside ? state.pressed : false );
		}
		else if ( event.Type == sf::Event::MouseButtonPressed and event.MouseButton.Button == sf::Mouse::Left )
		{
			mousePos = sf::Vector2i( event.MouseButton.X, event.MouseButton.Y );
			state.pressed = spriteRect.Contains( mousePos );
		}
		else if ( event.Type == sf::Event::MouseButtonReleased and event.MouseButton.Button == sf::Mouse::Left )
		{
			mousePos = sf::Vector2i( event.MouseButton.X, event.MouseButton.Y );
			state.pressed = false;
		}
		
		// Only callback stuff is past here
		if ( !callback )
		{
			return;
		}
		
		if ( previousInside == false and state.inside == true )
		{
			callback( EventType::Enter, ( * this ) );
		}
		else if ( previousInside == true and state.inside == false )
		{
			callback( EventType::Exit, ( * this ) );
		}
		else if ( previousPress == false and state.pressed == true )
		{
			callback( EventType::Press, ( * this ) );
		}
		else if ( previousPress == true and state.pressed == false )
		{
			callback( EventType::Release, ( * this ) );
		}
	}
	
	void Button::Draw( sf::RenderWindow& window )
	{
		UpdateSpriteRect();
		window.Draw( sprite );
	}
	
	void Button::UpdateSpriteRect()
	{
		if ( state.pressed )
		{
			sprite.SetSubRect( rects.press );
		}
		else if ( state.inside )
		{
			sprite.SetSubRect( rects.hover );
		}
		else
		{
			sprite.SetSubRect( rects.idle );
		}
	}
}
