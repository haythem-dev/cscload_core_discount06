//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		result struct for remote procedure calls
 *  \author		Steffen Heinlein
 *  \date		26.06.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_REMOTEPROCEDURERESULT_H
#define GUARD_LIBCSC_UTILS_REMOTEPROCEDURERESULT_H

namespace libcsc_utils
{	
	struct RemoteProcedureResult
	{
		bool				m_Success;
        	basar::Int32        m_DatasetsProcessed;
		basar::VarString	m_InfoMessage;

        RemoteProcedureResult(const bool success, const basar::Int32 datasetsProcessed, const basar::VarString& message = "")
			: m_Success(success),m_DatasetsProcessed(datasetsProcessed), m_InfoMessage( message )
		{}		
	};

}
#endif  // GUARD_LIBCSC_UTILS_REMOTEPROCEDURERESULT_H
