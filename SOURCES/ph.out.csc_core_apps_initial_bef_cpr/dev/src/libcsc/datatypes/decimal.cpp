#include "decimal.h"
#include <libbasarcmnutil_i18nstring.h>
#include "exceptions/propertyunsetexception.h"

namespace libcsc
{
const Decimal & Decimal::zero()
{
	static Decimal res( basar::Decimal( 0 ) );
	res.setClean();
	return res;
}

Decimal::Decimal()
: PropertyState( UNSET ),
  m_Value( 0.0 )
{
}

Decimal::Decimal( const libcsc::Decimal & rhs )
: PropertyState( UNSET ),
  m_Value( 0.0 )
{
	this->operator=( rhs );
}

Decimal::Decimal( const basar::Decimal & value )
: PropertyState( DIRTY ),
  m_Value( value )
{
}

Decimal::~Decimal()
{
}

libcsc::Decimal & Decimal::operator=( const libcsc::Decimal & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	m_Value = rhs.m_Value;
	setDirty();
	return *this;
}

libcsc::Decimal & Decimal::operator=( const basar::Decimal & value )
{
	if( &m_Value == &value )
	{
		return *this;
	}

	m_Value = value;
	setDirty();
	return *this;
}

Decimal::operator const basar::Decimal & () const
{
	checkState();
	return m_Value;
}

const basar::Decimal & Decimal::get() const
{
	return operator const basar::Decimal &();
}

bool Decimal::operator==( const libcsc::Decimal & rhs ) const
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

bool Decimal::operator!=( const libcsc::Decimal & rhs ) const
{
	return ( !this->operator==( rhs ) );
}

void Decimal::checkState() const
{
#ifndef NOCHECKS
	if( isUnset() )
	{
		throw exceptions::PropertyUnsetException( basar::ExceptInfo( "Decimal::checkState()", "Property is UNSET!", __FILE__, __LINE__ ) );
	}
#endif
}

std::ostream & Decimal::toStream( std::ostream & strm /* = std::cout */ ) const
{
	if( isUnset() )
	{
		strm << "UNSET";
	}
	else
	{
		strm << m_Value.toNonLocString().c_str() << " (" <<  *( dynamic_cast<const PropertyState *>( this ) ) << ")";
	}
	return strm;
}

} // end namespace libcsc
