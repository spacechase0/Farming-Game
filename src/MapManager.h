#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <SFML/Graphics.hpp>
#include <list>

#include "obj/Base.h"
#include "TileLayer.h"

class MapManager
{
	public:
		void Update();
		void Update( const sf::Event& event );
		void Draw( sf::RenderWindow& window );
		
		// Objects
		typedef boost::shared_ptr< obj::Base > ObjectPtr;
		typedef std::list< ObjectPtr > ObjectList;
		ObjectList menuObjects;
		
		// Maps
		struct Map
		{
			std::vector< TileLayer > layers;
			ObjectList objects;
		};
		typedef boost::shared_ptr< Map > MapPtr;
		std::map< std::string, MapPtr > maps;
		std::string currentMap;
		
		// Garbage
		void AddGarbage( ObjectList::iterator it, ObjectList* list );
		void AddMenuGarbage( ObjectList::iterator it );
		void CollectGarbage();
		
		// Misc
		inline const MapPtr& operator [] ( const std::string& str ) const { return maps.at( str ); }
		inline MapPtr& operator [] ( const std::string& str ) { return maps[ str ]; }
	
	private:
		typedef std::pair< ObjectList::iterator, ObjectList* > GarbagePair;
		std::list< GarbagePair > garbageObjects;
		
		void DrawLayer( sf::RenderWindow& window, const TileLayer& layer ) const;
		bool CompareObjects( const boost::shared_ptr< obj::Base >& obj1, const boost::shared_ptr< obj::Base >& obj2 );
};

#endif // MAPMANAGER_H
