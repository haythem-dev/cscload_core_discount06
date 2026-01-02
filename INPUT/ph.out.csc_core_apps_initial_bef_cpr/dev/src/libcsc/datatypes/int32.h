#ifndef GUARD_LIBCSC_INT32_H
#define GUARD_LIBCSC_INT32_H

#include <libbasar_definitions.h>
#include <datatypes/propertystate.h>
#include <iostream>

namespace libcsc
{
class Int32 : public PropertyState
{
public:
	Int32();
	Int32( const libcsc::Int32 & rhs ); 
	Int32( const basar::Int32 & value );
	~Int32();

	libcsc::Int32 & operator=( const libcsc::Int32 & rhs );
	libcsc::Int32 & operator=( const basar::Int32 & value );

	operator const basar::Int32 & () const;
	const basar::Int32 & get() const;

	bool operator==( const libcsc::Int32 & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	void checkState() const;

	basar::Int32	m_Value;
};

} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::Int32 & i )
{
    i.toStream( strm );
    return strm;
}

#endif // GUARD_LIBCSC_INT32_H
