//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief  interface declaration for tcaccess remote procedures
*   \author Steffen Heinlein
*   \date   20.06.2012
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_IREMOTEPROCEDURE_H
#define GUARD_LIBCSC_UTILS_IREMOTEPROCEDURE_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_bstring.h>
#include "remoteprocedureresult.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//

namespace libcsc_utils
{
	//-------------------------------------------------------------------------------------------------//
	// interface declaration
	//-------------------------------------------------------------------------------------------------//
	class IRemoteProcedure
	{
		public:		

			virtual ~IRemoteProcedure(){};		

			virtual const basar::VarString					getProcedureName() const = 0;

			virtual const basar::VarString					serializeQuery() const = 0;										 

			virtual void									deserializeResult(const basar::VarString &result) = 0;		 

			virtual const basar::VarString					serializeForLogging() const = 0 ;	

			virtual const libcsc_utils::RemoteProcedureResult		checkResult() const = 0;
	};

} // namespace util

#endif // GUARD_LIBCSC_UTILS_IREMOTEPROCEDURE_H
