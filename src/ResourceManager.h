#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <SFML/System/Mutex.hpp>
#include <string>

namespace sf
{
	class Texture;
	class SoundBuffer;
	class Font;
}

class ResourceManager
{
	public:
		static bool loadTexture( const std::string& filename );
		static bool loadSoundBuffer( const std::string& filename );
		static bool loadFont( const std::string& filename );
		
		static std::shared_ptr< sf::Texture > getTexture( const std::string& filename, bool loadIfNotLoaded = true );
		static std::shared_ptr< sf::SoundBuffer > getSoundBuffer( const std::string& filename, bool loadIfNotLoaded = true );
		static std::shared_ptr< sf::Font > getFont( const std::string& filename, bool loadIfNotLoaded = true );
		
		static void unloadTexture( const std::string& filename );
		static void unloadSoundBuffer( const std::string& filename );
		static void unloadFont( const std::string& filename );
		static void unloadAll();
	
	private:
		~ResourceManager() = delete;
		
		static sf::Mutex texMutex;
		static sf::Mutex soundMutex;
		static sf::Mutex fontMutex;
		
		static std::map< std::string, std::shared_ptr< sf::Texture > > textures;
		static std::map< std::string, std::shared_ptr< sf::SoundBuffer > > soundBuffers;
		static std::map< std::string, std::shared_ptr< sf::Font > > fonts;
};

#endif // RESOURCEMANAGER_H
