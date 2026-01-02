#include "datetime.h"
#include <libbasarcmnutil_i18nstring.h>
#include <libbasar_pkgversion.h>
#include "exceptions/propertyunsetexception.h"

namespace libcsc
{
DateTime::DateTime()
: PropertyState( UNSET ),
#if PRODUCT_VERSION >= 1120000
  m_Value( basar::cmnutil::NULLVAL_SQL_DATE, basar::cmnutil::NULLVAL_SQL_TIME )
#else
  m_Value( NULLVAL_SQL_DATE, NULLVAL_SQL_TIME )
#endif 
{
}

DateTime::DateTime( const libcsc::DateTime & rhs )
: PropertyState( UNSET ),
#if PRODUCT_VERSION >= 1120000
  m_Value( basar::cmnutil::NULLVAL_SQL_DATE, basar::cmnutil::NULLVAL_SQL_TIME )
#else
  m_Value( NULLVAL_SQL_DATE, NULLVAL_SQL_TIME )
#endif 
{
	this->operator=( rhs );
}

DateTime::DateTime( const basar::DateTime & value )
: PropertyState( DIRTY ),
  m_Value( value )
{
}

DateTime::~DateTime()
{
}

libcsc::DateTime & DateTime::operator=( const libcsc::DateTime & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	m_Value = rhs.m_Value;
	setDirty();
	return *this;
}

libcsc::DateTime & DateTime::operator=( const basar::DateTime & value )
{
	if( &m_Value == &value )
	{
		return *this;
	}

	m_Value = value;
	setDirty();
	return *this;
}

DateTime::operator const basar::DateTime & () const
{
	checkState();
	return m_Value;
}

bool DateTime::operator==( const libcsc::DateTime & rhs ) const
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

void DateTime::checkState() const
{
#ifndef NOCHECKS
	if( isUnset() )
	{
		throw exceptions::PropertyUnsetException( basar::ExceptInfo( "DateTime::checkState()", "Property is UNSET!", __FILE__, __LINE__ ) );
	}
#endif
}

std::ostream & DateTime::toStream( std::ostream & strm /* = std::cout */ ) const
{
	if( isUnset() )
	{
		strm << "UNSET";
	}
	else
	{
		strm << m_Value.toStrDateTime().c_str() << " (" <<  *( dynamic_cast<const PropertyState *>( this ) ) << ")";
	}
	return strm;
}

} // end namespace libcsc
