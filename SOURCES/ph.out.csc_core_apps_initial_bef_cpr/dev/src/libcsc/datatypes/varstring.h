#ifndef GUARD_LIBCSC_VARSTRING_H
#define GUARD_LIBCSC_VARSTRING_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <datatypes/propertystate.h>
#include <string>
#include <iostream>

namespace libcsc
{
class VarString : public PropertyState
{
public:
	VarString();
	VarString( const libcsc::VarString & rhs ); 
	VarString( const basar::VarString & value );
	VarString( const std::string & value );
	VarString( const char * value );
	~VarString();

	libcsc::VarString & operator=( const libcsc::VarString & rhs );
	libcsc::VarString & operator=( const basar::VarString & value );
	libcsc::VarString & operator=( const std::string & value );
	libcsc::VarString & operator=( const char * value );

	bool operator==( const libcsc::VarString & rhs ) const;
	bool operator==( const basar::VarString & value ) const;
	bool operator==( const std::string & value ) const;
	bool operator==( const char * value ) const;

	bool operator!=( const libcsc::VarString & rhs ) const;
	bool operator!=( const basar::VarString & value ) const;
	bool operator!=( const std::string & value ) const;
	bool operator!=( const char * value ) const;

	operator const basar::VarString & () const;

    const char * c_str() const;
	std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	void checkState() const;

	basar::VarString	m_Value;
};

} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::VarString & s )
{
    s.toStream( strm );
    return strm;
}



#endif // GUARD_LIBCSC_VARSTRING_H
