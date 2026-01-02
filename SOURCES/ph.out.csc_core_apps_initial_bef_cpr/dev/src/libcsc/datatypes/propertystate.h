#ifndef GUARD_LIBCSC_PROPERTY_STATE_H
#define GUARD_LIBCSC_PROPERTY_STATE_H

#include "propertystateenum.h"
#include <iostream>

namespace libcsc
{
class PropertyState
{
public:
	PropertyState();
	PropertyState( const PropertyStateEnum state );
	bool operator==( const PropertyState & rhs ) const;

	void setState( const PropertyStateEnum state );
	void setUnset();
	void setClean();
	void setDirty();

	PropertyStateEnum getState() const;
	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

protected:
	virtual ~PropertyState();

private:
	PropertyStateEnum	m_State;
};

} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::PropertyState & ps )
{
    ps.toStream( strm );
    return strm;
}

#endif // GUARD_LIBCSC_PROPERTY_STATE_H
