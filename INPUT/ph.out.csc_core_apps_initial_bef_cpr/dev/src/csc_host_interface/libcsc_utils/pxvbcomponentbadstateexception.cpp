//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief		exception for failed initialization of pxVerbund objects
 *  \author		Marco Köppendörfer
 *  \date		22.08.2012
 *  \version	00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "pxvbcomponentbadstateexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

	//--------------------------------------------------------------------------------------------------//
	PXVBComponentBadStateException::PXVBComponentBadStateException( const basar::ExceptInfo& sInfo )
		: BasarException( sInfo, "PXVBComponentBadStateException" )
	{}

	//--------------------------------------------------------------------------------------------------//
	PXVBComponentBadStateException::~PXVBComponentBadStateException()
	{}

} // namespace util
