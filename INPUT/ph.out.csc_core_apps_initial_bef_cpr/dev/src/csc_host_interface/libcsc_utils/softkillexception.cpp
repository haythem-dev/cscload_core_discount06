//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief exception from soft kill signals
 *  \author Heinlein Steffen
 *  \date 15.06.2012
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "softkillexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

SoftKillException::SoftKillException( const basar::ExceptInfo& sInfo )
	: BasarException( sInfo, "SoftKillException" )
{
}

SoftKillException::~SoftKillException()
{
}

} // end namespace csc_phatra
