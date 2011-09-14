#ifndef GUI_BASE_H
#define GUI_BASE_H

namespace gui
{
	class Base
	{
		public:
			~Base() {};
			
			virtual void Update( sf::RenderWindow& window ) = 0;
			virtual void Update( sf::RenderWindow& window, const sf::Event& event ) = 0;
			virtual void Draw( sf::RenderWindow& window ) = 0;
	};
}

#endif // GUI_BASE_H
