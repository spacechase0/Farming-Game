#ifndef SCENES_SCENEMAINMENU_H
#define SCENES_SCENEMAINMENU_H

#include <SFML/Graphics.hpp>

#include "scenes/SceneBase.h"
#include "gui/Gui.h"

class SceneMainMenu : public SceneBase
{
	public:
		SceneMainMenu( Game& theGame );
		
		virtual void Initialize();
		virtual void Terminate();
		
		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );
	
	private:
		gui::TextButton button;
		
		void ButtonCallback( gui::Button::EventType type, gui::Button& button );
};

#endif // SCENES_SCENEMAINMENU_H
