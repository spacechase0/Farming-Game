#ifndef UTIL_VERSIONMANAGER_H
#define UTIL_VERSIONMANAGER_H

#include <array>

namespace util
{
	template < typename T >
	class VersionManager
	{
		public:
			void addVersion( T t );
			T getVersion( std::size_t version ) const;
			std::size_t getVersionCount() const;
		
		private:
			std::vector< T > versions;
	};
	
	#include <util/VersionManager.inl>
}


#endif // UTIL_VERSIONMANAGER_H
