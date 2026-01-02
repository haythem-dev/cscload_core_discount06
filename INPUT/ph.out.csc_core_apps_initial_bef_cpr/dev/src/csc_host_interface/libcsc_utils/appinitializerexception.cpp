//--------------------------------------------------------------------------------------------------//
/*! \file commandlineexception.cpp
 *  \brief exception from parsing the command line
 *  \author Dirk Kapusta
 *  \date 21.10.2008
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
//#include "cmnexcept.h"
#include <libbasar_definitions.h>
#include "appinitializerexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

AppInitializerException::AppInitializerException( const basar::ExceptInfo& sInfo )
: BasarException( sInfo, "AppInitializerException" )
{
}

AppInitializerException::~AppInitializerException()
{
}

} // end namespace util
