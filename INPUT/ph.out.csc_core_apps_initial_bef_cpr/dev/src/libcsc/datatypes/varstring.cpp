#include "varstring.h"
#include "exceptions/propertyunsetexception.h"

namespace libcsc
{
VarString::VarString()
: PropertyState( UNSET ),
  m_Value( "" )
{
}

VarString::VarString( const libcsc::VarString & rhs )
: PropertyState( UNSET ),
  m_Value( "" )
{
	this->operator=( rhs );
}

VarString::VarString( const basar::VarString & value )
: PropertyState( DIRTY ),
  m_Value( value )
{
}

VarString::VarString( const std::string & value )
: PropertyState( DIRTY ),
  m_Value( value )
{
}

VarString::VarString( const char * value )
: PropertyState( DIRTY ),
  m_Value( value )
{
}

VarString::~VarString()
{
}

libcsc::VarString & VarString::operator=( const libcsc::VarString & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	m_Value = rhs.m_Value;
	setDirty();
	return *this;
}

libcsc::VarString & VarString::operator=( const basar::VarString & value )
{
	if( &m_Value == &value )
	{
		return *this;
	}

	m_Value = value;
	setDirty();
	return *this;
}

libcsc::VarString & VarString::operator=( const std::string & value )
{
	m_Value = value;
	setDirty();
	return *this;
}

libcsc::VarString & VarString::operator=( const char * value )
{
	m_Value = value;
	setDirty();
	return *this;
}

bool VarString::operator==( const libcsc::VarString & rhs ) const
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

bool VarString::operator==( const basar::VarString & value ) const
{
	if( isUnset() )
	{
		return false;
	}

	return ( m_Value == value );
}

bool VarString::operator==( const std::string & value ) const
{
	if( isUnset() )
	{
		return false;
	}

	return ( m_Value == value );
}

bool VarString::operator==( const char * value ) const
{
	if( isUnset() )
	{
		return false;
	}

	return ( m_Value == value );
}

bool VarString::operator!=( const libcsc::VarString & rhs ) const
{
	return !( operator==( rhs ) );
}

bool VarString::operator!=( const basar::VarString & value ) const
{
	return !( operator==( value ) );
}

bool VarString::operator!=( const std::string & value ) const
{
	return !( operator==( value ) );
}

bool VarString::operator!=( const char * value ) const
{
	return !( operator==( value ) );
}

VarString::operator const basar::VarString & () const
{
	checkState();
	return m_Value;
}

void VarString::checkState() const
{
#ifndef NOCHECKS
	if( isUnset() )
	{
		throw exceptions::PropertyUnsetException( basar::ExceptInfo( "VarString::checkState()", "Property is UNSET!", __FILE__, __LINE__ ) );
	}
#endif
}

const char * VarString::c_str() const
{
	checkState();
    return m_Value.c_str();
}

std::ostream & VarString::toStream( std::ostream & strm /* = std::cout */ ) const
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

} // end namespace libcsc
