//--------------------------------------------------------------------------------------------------//
/*! \file		notimplementedexception.cpp
 *  \brief      exception for missing implementations
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
//#include "cmnexcept.h"
#include <libbasar_definitions.h>
#include "notimplementedexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	NotImplementedException::NotImplementedException(const basar::ExceptInfo& sInfo) :
			BasarException(sInfo, "NotImplementedException")
	{
	}

	NotImplementedException::~NotImplementedException()
	{
	}
} // end namespace util
