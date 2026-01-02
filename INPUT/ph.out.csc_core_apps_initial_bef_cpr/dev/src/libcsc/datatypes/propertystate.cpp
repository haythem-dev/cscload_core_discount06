#include "propertystate.h"

namespace libcsc
{
PropertyState::PropertyState()
: m_State( UNSET )
{
}

PropertyState::PropertyState( const PropertyStateEnum state )
: m_State( state )
{
}

PropertyState::~PropertyState()
{
}

bool PropertyState::operator==( const PropertyState & rhs ) const
{
	return ( m_State == rhs.m_State );
}

void PropertyState::setState( const PropertyStateEnum state )
{
	m_State = state;
}

void PropertyState::setUnset()
{
	m_State = UNSET;
}

void PropertyState::setClean()
{
	m_State = CLEAN;
}

void PropertyState::setDirty()
{
	m_State = DIRTY;
}

PropertyStateEnum PropertyState::getState() const
{
	return m_State;
}

bool PropertyState::isUnset() const
{
	return ( UNSET == m_State );
}

bool PropertyState::isClean() const
{
	return ( CLEAN == m_State );
}

bool PropertyState::isDirty() const
{
	return ( DIRTY == m_State );
}

std::ostream & PropertyState::toStream( std::ostream & strm /* = std::cout */ ) const
{
	switch( m_State )
	{
		case UNSET: strm << "UNSET"; break;
		case CLEAN: strm << "CLEAN"; break;
		case DIRTY: strm << "DIRTY"; break;
		default: strm << "-UNDEFINED- (" << m_State << ")"; 
	}
	return strm;
}

} // end namespace libcsc
