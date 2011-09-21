#ifndef UTIL_TYPE_H
#define UTIL_TYPE_H

namespace util
{
	template< typename TC, typename TP >
	bool IsOfType( TP parameter )
	{
		return dynamic_cast< TC >( parameter );
	}
}

#endif // UTIL_TYPE_H
