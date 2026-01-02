//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating inconsistant config values
 *  \author     Marco Köppendörfer
 *  \date       10.01.2013
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "configdatainconsistantexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

ConfigDataInconsistantException::ConfigDataInconsistantException( const basar::ExceptInfo& sInfo )
: BasarException( sInfo, "ConfigDataInconsistantException" )
{
}

ConfigDataInconsistantException::~ConfigDataInconsistantException()
{
}

} // end namespace util
