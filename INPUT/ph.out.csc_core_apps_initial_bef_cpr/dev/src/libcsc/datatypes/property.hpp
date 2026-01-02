#ifndef GUARD_LIBCSC_PROPERTY_H
#define GUARD_LIBCSC_PROPERTY_H

#include <libbasar_definitions.h>
#include <datatypes/propertystate.h>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <exceptions/propertyunsetexception.h>

namespace libcsc
{
template< typename T >
class Property : public PropertyState
{
public:
	Property()
	: PropertyState( UNSET )
	{
	}
	
	Property( const libcsc::Property<T> & rhs )
	: PropertyState( UNSET )
	{
		this->operator=( rhs );
	}

	Property( const T & value )
	: PropertyState( DIRTY ),
	  m_Value( value )
	{
	}

	virtual ~Property()
	{
	}

	libcsc::Property<T> & operator=( const libcsc::Property<T> & rhs )
	{
		if( this == &rhs )
		{
			return *this;
		}

		m_Value = rhs.m_Value;
		setDirty();
		return *this;
	}

	libcsc::Property<T> & operator=( const T & value )
	{
		if( &m_Value == &value )
		{
			return *this;
		}

		m_Value = value;
		setDirty();
		return *this;
	}

	operator const T & () const
	{
		checkState();
		return m_Value;
	}

	const T & get() const
	{
		return operator const T &();
	}

	bool operator==( const libcsc::Property<T> & rhs ) const
	{
		if( this == &rhs )
		{
			return true;
		}

		if(    isUnset()
			&& rhs.isUnset() )
		{
			return true;
		}

		if(    isUnset()
			|| rhs.isUnset() )
		{
			return false;
		}

		return ( m_Value == rhs.m_Value );
	}

	std::ostream & toStream( std::ostream & strm = std::cout ) const
	{
		if( isUnset() )
		{
			strm << "UNSET";
		}
		else
		{
			strm << m_Value << " (" <<  *( dynamic_cast<const PropertyState *>( this ) ) << ")";
		}
		return strm;
	}

private:
	void checkState() const
	{
#ifndef NOCHECKS
		if( isUnset() )
		{
			std::stringstream ss;
			ss << "Property<" << typeid( T ).name() << ">::checkState()";
			throw exceptions::PropertyUnsetException( basar::ExceptInfo( ss.str().c_str(), "Property is UNSET!", __FILE__, __LINE__ ) );
		}
#endif
	}

	T	m_Value;
};

} // end namespace libcsc

template< typename T >
inline std::ostream & operator<<( std::ostream & strm, const libcsc::Property<T> & p )
{
	p.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_PROPERTY_H
