#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H

#include <SFML/Graphics.hpp>

#include "scenes/SceneBase.h"

class SceneMainMenu : public SceneBase
{
	public:
		SceneMainMenu( FarmingGame& theGame );
		
		virtual void Initialize();
		virtual void Terminate();
		
		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );
	
	private:
		sf::Texture& buttonTex;
};

#endif // SCENEMAINMENU_H
