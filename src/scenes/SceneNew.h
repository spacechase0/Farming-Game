#ifndef SCENES_SCENENEW_H
#define SCENES_SCENENEW_H

#include <SFML/Graphics.hpp>

#include "scenes/SceneGuiBase.h"

class SceneNew : public SceneGuiBase
{
	public:
		SceneNew( Game& theGame );

		virtual void Initialize();
		virtual void Terminate();

		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );

	private:
		sf::Text title;

		void CreateButton( const std::string& text, sf::Vector2f pos, sf::Texture& tex, sf::Font& font, size_t charSize );
		void ButtonCallback( gui::Button::EventType type, gui::Button& button );
};

#endif // SCENES_SCENENEW_H
