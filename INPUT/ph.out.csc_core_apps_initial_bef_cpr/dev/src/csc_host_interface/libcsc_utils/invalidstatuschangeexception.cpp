//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief exception from invalid status changes
 *  \author Heinlein Steffen
 *  \date 10.07.2012
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "invalidstatuschangeexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

InvalidStatusChangeException::InvalidStatusChangeException( const basar::ExceptInfo& sInfo )
	: BasarException( sInfo, "InvalidStatusChangeException" )
{
}

InvalidStatusChangeException::~InvalidStatusChangeException()
{
}

} // end namespace csc_phatra
