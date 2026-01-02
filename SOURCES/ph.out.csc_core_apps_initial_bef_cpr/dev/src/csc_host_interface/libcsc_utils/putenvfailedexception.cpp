//--------------------------------------------------------------------------------------------------//
/*! \file		putenvfailedexception.cpp
 *  \brief      exception for failed putenv
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
//#include "cmnexcept.h"
#include <libbasar_definitions.h>
#include "putenvfailedexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	PutenvFailedException::PutenvFailedException(const basar::ExceptInfo& sInfo) :
			BasarException(sInfo, "PutenvFailedException")
	{
	}

	PutenvFailedException::~PutenvFailedException()
	{
	}
} // end namespace csc_phatra
