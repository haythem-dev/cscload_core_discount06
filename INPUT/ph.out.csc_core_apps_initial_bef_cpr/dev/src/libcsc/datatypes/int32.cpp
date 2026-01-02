#include "int32.h"
#include "exceptions/propertyunsetexception.h"

namespace libcsc
{
Int32::Int32()
: PropertyState( UNSET ),
  m_Value( 0 )
{
}

Int32::Int32( const libcsc::Int32 & rhs )
: PropertyState( UNSET ),
  m_Value( 0 )
{
	this->operator=( rhs );
}

Int32::Int32( const basar::Int32 & value )
: PropertyState( DIRTY ),
  m_Value( value )
{
}

Int32::~Int32()
{
}

libcsc::Int32 & Int32::operator=( const libcsc::Int32 & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	m_Value = rhs.m_Value;
	setDirty();
	return *this;
}

libcsc::Int32 & Int32::operator=( const basar::Int32 & value )
{
	if( &m_Value == &value )
	{
		return *this;
	}

	m_Value = value;
	setDirty();
	return *this;
}

Int32::operator const basar::Int32 & () const
{
	checkState();
	return m_Value;
}

const basar::Int32 & Int32::get() const
{
	return operator const basar::Int32 &();
}

bool Int32::operator==( const libcsc::Int32 & rhs ) const
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

void Int32::checkState() const
{
#ifndef NOCHECKS
	if( isUnset() )
	{
		throw exceptions::PropertyUnsetException( basar::ExceptInfo( "Int32::checkState()", "Property is UNSET!", __FILE__, __LINE__ ) );
	}
#endif
}

std::ostream & Int32::toStream( std::ostream & strm /* = std::cout */ ) const
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
