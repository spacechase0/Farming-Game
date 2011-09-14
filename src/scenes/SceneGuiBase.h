#ifndef SCENES_SCENESGUIBASE_H
#define SCENES_SCENESGUIBASE_H

#include <vector>

#include "scenes/SceneBase.h"
#include "gui/Gui.h"

class SceneGuiBase : public SceneBase
{
	public:
		SceneGuiBase( Game& theGame );
		
		virtual void Initialize();
		virtual void Terminate();
		
		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
	
	protected:
		std::vector< boost::shared_ptr< gui::Base > > gui;
		
		void DrawGui( sf::RenderWindow& window );
};

#endif // SCENES_SCENESGUIBASE_H
