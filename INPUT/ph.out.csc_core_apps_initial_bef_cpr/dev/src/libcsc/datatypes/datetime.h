#ifndef GUARD_LIBCSC_DATETIME_H
#define GUARD_LIBCSC_DATETIME_H

#include <libbasarcmnutil_datetime.h>
#include <datatypes/propertystate.h>
#include <iostream>

namespace libcsc
{
class DateTime : public PropertyState
{
public:
	DateTime();
	DateTime( const libcsc::DateTime & rhs ); 
	DateTime( const basar::DateTime & value );
	~DateTime();

	libcsc::DateTime & operator=( const libcsc::DateTime & rhs );
	libcsc::DateTime & operator=( const basar::DateTime & value );

	operator const basar::DateTime & () const;

	bool operator==( const libcsc::DateTime & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	void checkState() const;

	basar::DateTime	m_Value;
};

} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::DateTime & d )
{
    d.toStream( strm );
    return strm;
}

#endif // GUARD_LIBCSC_DATETIME_H
