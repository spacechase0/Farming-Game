#include "ResourceManager.h"

#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Lock.hpp>

namespace
{
	template < class RESOURCE >
	bool load( sf::Mutex& mutex, std::map< std::string, std::shared_ptr< RESOURCE > >& resources, const std::string& filename )
	{
		sf::Lock lock( mutex );
		
		auto found = resources.find( filename );
		if ( found == resources.end() )
		{
			std::shared_ptr< RESOURCE > res( new RESOURCE() );
			if ( !res->loadFromFile( filename ) )
			{
				std::cout << "Failed to load " << filename << "!" << std::endl;
				return false;
			}
			
			resources.insert( std::make_pair( filename, res ) );
		}
		else
		{
			if ( !found->second->loadFromFile( filename ) )
			{
				std::cout << "Failed to load " << filename << "!" << std::endl;
				return false;
			}
		}
		
		return true;
	}
	
	template < class RESOURCE >
	std::shared_ptr< RESOURCE > get( sf::Mutex& mutex, std::map< std::string, std::shared_ptr< RESOURCE > >& resources, const std::string& filename, bool loadIfNotLoaded )
	{
		sf::Lock lock( mutex );
		
		auto found = resources.find( filename );
		if ( found == resources.end() )
		{
			if ( loadIfNotLoaded )
			{
				load( mutex, resources, filename );
				return get( mutex, resources, filename, false );
			}
		}
		else
		{
			return found->second;
		}
		
		return std::shared_ptr< RESOURCE >();
	}
	
	template < class RESOURCE >
	void unload( sf::Mutex& mutex, std::map< std::string, std::shared_ptr< RESOURCE > >& resources, const std::string& filename )
	{
		sf::Lock lock( mutex );
		
		auto found = resources.find( filename );
		if ( found != resources.end() )
		{
			resources.erase( found );
		}
	}
}

sf::Mutex ResourceManager::texMutex;
sf::Mutex ResourceManager::soundMutex;
sf::Mutex ResourceManager::fontMutex;

std::map< std::string, std::shared_ptr< sf::Texture > > ResourceManager::textures;
std::map< std::string, std::shared_ptr< sf::SoundBuffer > > ResourceManager::soundBuffers;
std::map< std::string, std::shared_ptr< sf::Font > > ResourceManager::fonts;

bool ResourceManager::loadTexture( const std::string& filename )
{
	return load( texMutex, textures, filename );
}

bool ResourceManager::loadSoundBuffer( const std::string& filename )
{
	return load( soundMutex, soundBuffers, filename );
}

bool ResourceManager::loadFont( const std::string& filename )
{
	return load( fontMutex, fonts, filename );
}

std::shared_ptr< sf::Texture > ResourceManager::getTexture( const std::string& filename, bool loadIfNotLoaded )
{
	return get( texMutex, textures, filename, loadIfNotLoaded );
}

std::shared_ptr< sf::SoundBuffer > ResourceManager::getSoundBuffer( const std::string& filename, bool loadIfNotLoaded )
{
	return get( soundMutex, soundBuffers, filename, loadIfNotLoaded );
}

std::shared_ptr< sf::Font > ResourceManager::getFont( const std::string& filename, bool loadIfNotLoaded )
{
	return get( fontMutex, fonts, filename, loadIfNotLoaded );
}

void ResourceManager::unloadTexture( const std::string& filename )
{
	unload( texMutex, textures, filename );
}

void ResourceManager::unloadSoundBuffer( const std::string& filename )
{
	unload( soundMutex, soundBuffers, filename );
}

void ResourceManager::unloadFont( const std::string& filename )
{
	unload( fontMutex, fonts, filename );
}

void ResourceManager::unloadAll()
{
	sf::Lock texLock( texMutex );
	sf::Lock soundLock( soundMutex );
	sf::Lock fontLock( fontMutex );
	
	textures.clear();
	soundBuffers.clear();
	fonts.clear();
}
