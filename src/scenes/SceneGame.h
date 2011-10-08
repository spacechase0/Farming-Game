#ifndef SCENES_SCENEGAME_H
#define SCENES_SCENEGAME_H

#include <vector>
#include <list>

#include "scenes/SceneBase.h"
#include "TileLayer.h"
#include "util/Grid.h"
#include "item/Items.h"
#include "MapManager.h"
#include "ColorScale.h"

namespace obj
{
	class Base;
	class GridObject;
	class Player;
	class CameraController;
	class Debug;
	class DialogIngameGui;
}

class SceneGame : public SceneBase
{
	public:
		SceneGame( Game& game );

		virtual void Initialize();
		virtual void Terminate();

		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );

		// Items
		typedef boost::shared_ptr< item::Item > ItemPtr;
		std::map< std::string, ItemPtr > itemDefs;

		// Maps
		MapManager maps;

		// Tiles
		bool IsTileEmpty( MapManager::Map& map, int x, int y );
		bool IsTileEmpty( MapManager::Map& map, sf::Vector2i pos );

		// Misc
		obj::Player* player;
		obj::CameraController* cameraController;
		obj::DialogIngameGui* ingameGui;
		obj::Debug* debug;
		bool simulateWorld;
		
		sf::Uint16 GetTime() const;
		std::string GetTimeString() const;
		
		enum WeatherType
		{
			None,
			Rain
		};

		void CreateChatDialog( const std::vector< std::string >& messages );

	private:
		sf::Uint16 time;
		sf::Image timeGradient;
		WeatherType weather;
		float weatherHeight;
		
		void RandomizeWeather();
		void DrawWeather( sf::RenderWindow& window );
		void DrawTime( sf::RenderWindow& window );
		
		void LoadMap( const std::string& mapName );
		void CreatePlayer();

		void LoadItems( const std::string& filename );
		item::Item::Type ToType( const std::string& str );
		item::Tool::Action ToAction( const std::string& str );
};

#endif // SCENES_SCENEGAME_H
