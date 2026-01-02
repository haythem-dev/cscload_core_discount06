//--------------------------------------------------------------------------------------------------//
/*! \file configexception.cpp
*  \brief      exception for config
*  \author     Andre Egerer
*  \date       23.04.2012
*/ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
//#include "cmnexcept.h"
#include <libbasar_definitions.h>
#include "configException.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	namespace config
	{
		ConfigException::ConfigException( const basar::ExceptInfo& sInfo )
			: BasarException( sInfo, "ConfigException" )
		{
		}

		ConfigException::~ConfigException()
		{
		}
	}
} // end namespace csc_phatra
