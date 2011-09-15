#ifndef UTIL_GRID_H
#define UTIL_GRID_H

#include <vector>

namespace util
{
	template< typename T >
	class Grid : public std::vector< std::vector< T > >
	{
		public:
			Grid() : std::vector< std::vector< T > >() {}
			//Grid( const Grid& grid ) : std::vector< std::vector< T > >( grid ) {}
			explicit Grid( size_t n, const std::vector< T >& value = std::vector< T >() ) : std::vector< std::vector< T > >( n, value ) {}
	};
}

#endif // UTIL_GRID_H
