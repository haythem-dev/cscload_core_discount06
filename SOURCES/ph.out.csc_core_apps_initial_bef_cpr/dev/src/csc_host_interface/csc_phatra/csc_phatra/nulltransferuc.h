//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_NULLTRANSFERUC_H
#define GUARD_NULLTRANSFERUC_H

//-------------------------------------------------------------------------------------------//

#include "itransferuc.h"

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

class NullTransferUC : public ITransferUC
{
public:
	NullTransferUC(libcsc_utils::ICSC_LoggerPtr csc_logger)
	{
		m_CSC_Logger = csc_logger;
	}
	virtual ~NullTransferUC()
	{
	}

	virtual basar::appl::EventReturnStruct run()
	{
		METHODNAME_DEF( NullTransferUC, doRun );
		BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

		return basar::appl::EventReturnStruct();
	}
	virtual basar::Int32 getRecordsProcessed()
	{
		return 0;
	};
	
private:
	libcsc_utils::ICSC_LoggerPtr m_CSC_Logger;
};

//-------------------------------------------------------------------------------------------//

} //namespace useCase
} //namespace csc_phatra

//-------------------------------------------------------------------------------------------//

#endif // GUARD_NULLTRANSFERUC_H

//-------------------------------------------------------------------------------------------//
