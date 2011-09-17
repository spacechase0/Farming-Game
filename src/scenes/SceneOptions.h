#ifndef SCENES_SCENEOPTIONS_H
#define SCENES_SCENEOPTIONS_H

#include <SFML/Graphics.hpp>

#include "scenes/SceneGuiBase.h"

class SceneOptions : public SceneGuiBase
{
	public:
		SceneOptions( Game& theGame );

		virtual void Initialize();
		virtual void Terminate();

		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );

	private:
		sf::Text title;

		void ButtonCallback( gui::Button::EventType type, gui::Button& button );
};

#endif // SCENES_SCENEOPTIONS_H
