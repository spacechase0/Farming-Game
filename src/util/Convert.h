#ifndef UTIL_CONVERT_H
#define UTIL_CONVERT_H

#include <sstream>
#include <string>

namespace util
{
	template< typename T >
	T FromString( const std::string& str )
	{
		T tmp;
		
		std::stringstream ss;
		ss << str;
		ss >> tmp;
		
		return tmp;
	}
	
	template< typename T >
	std::string ToString( const T& t )
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
}

#endif // UTIL_CONVERT_H
