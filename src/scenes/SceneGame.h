#ifndef SCENES_SCENEGAME_H
#define SCENES_SCENEGAME_H

#include "scenes/SceneBase.h"

class SceneGame : public SceneBase
{
	public:
		SceneGame( Game& game );
		
		virtual void Initialize();
		virtual void Terminate();
		
		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );
	
	protected:
		// Coming soon
};

#endif // SCENES_SCENEGAME_H
