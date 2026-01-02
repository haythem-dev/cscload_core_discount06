#include "stringtransformer.h"
#include "libbasarcmnutil.h"
#include <pxsess.hpp>

namespace domMod
{
namespace corpha
{
namespace ProcessOrderDM
{
	// Initialize the static member variable
	basar::VarString StringTransformer::m_Country = "";

	//-------------------------------------------------------------------------------------------//
	StringTransformer::StringTransformer()
	{
	}
	
	//-------------------------------------------------------------------------------------------//
	StringTransformer::~StringTransformer()
	{
	}

	//-------------------------------------------------------------------------------------------//
	void StringTransformer::setCountry(const basar::VarString & country)
	{
		m_Country = country;
	}
								
	//-------------------------------------------------------------------------------------------//
	basar::VarString& StringTransformer::transform( basar::VarString& str )
	{
		// Make a "deep copy" of current locale name
		std::string prev_loc = std::setlocale( LC_ALL, NULL );

#ifndef WIN32
		if ( m_Country == pxSession::COUNTRY_BULGARIA )
		{
			std::setlocale( LC_ALL, "bg_BG.ISO8859-5" );
		}
		else
		{
			std::setlocale( LC_ALL, "en_US.ISO8859-1" );
		}
#endif

		// Replace non-printable characters with '_'
		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			// Check if a character is printable ( based on the locale! )
			if ( !std::isprint( str[i] ) )
			{
				str[i] = '_';
			}
		}

		// Restore the previous locale
		std::setlocale( LC_ALL, prev_loc.c_str() );

		return str;
	}			
}
}
}