#ifndef GUARD_LIBCSC_DECIMAL_H
#define GUARD_LIBCSC_DECIMAL_H

#include <libbasarcmnutil_decimal.h>
#include <datatypes/propertystate.h>
#include <iostream>

namespace libcsc
{
class Decimal : public PropertyState
{
public:
	static const Decimal & zero();

	Decimal();
	Decimal( const libcsc::Decimal & rhs ); 
	Decimal( const basar::Decimal & value );
	~Decimal();

	libcsc::Decimal & operator=( const libcsc::Decimal & rhs );
	libcsc::Decimal & operator=( const basar::Decimal & value );

	operator const basar::Decimal & () const;
	const basar::Decimal & get() const;

	bool operator==( const libcsc::Decimal & rhs ) const;
	bool operator!=( const libcsc::Decimal & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	void checkState() const;

	basar::Decimal	m_Value;
};

} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::Decimal & d )
{
    d.toStream( strm );
    return strm;
}

#endif // GUARD_LIBCSC_DECIMAL_H
