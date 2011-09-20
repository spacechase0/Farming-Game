#ifndef SCENES_SCENEMAINMENU_H
#define SCENES_SCENEMAINMENU_H

#include <SFML/Graphics.hpp>

#include "scenes/SceneGuiBase.h"

class SceneMainMenu : public SceneGuiBase
{
	public:
		SceneMainMenu( Game& theGame );
		
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

#endif // SCENES_SCENEMAINMENU_H
