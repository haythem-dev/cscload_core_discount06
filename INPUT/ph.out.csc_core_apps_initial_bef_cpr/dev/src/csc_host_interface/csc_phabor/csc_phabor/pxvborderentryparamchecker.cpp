//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmndm.h"

#include "pxvborderentryparamchecker.h"
#include "pxorderentryparamptr.h"
#include <icsc_logger.h>

#include "pvhx04_includes.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

//--------------------------------------------------------------------------------------------------//
	PXVBOrderEntryParamChecker::PXVBOrderEntryParamChecker( pxOrderEntryParamPtr oeparam, libcsc_utils::ICSC_LoggerPtr csc_logger )
		: m_CSC_Logger( csc_logger ), m_pxOrderEntryParam( oeparam )
	{
        METHODNAME_DEF( PXVBOrderEntryParamChecker, PXVBOrderEntryParamChecker )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBOrderEntryParamChecker::~PXVBOrderEntryParamChecker()
	{
        METHODNAME_DEF( PXVBOrderEntryParamChecker, ~PXVBOrderEntryParamChecker )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	bool PXVBOrderEntryParamChecker::checkNarcoticsTransfer() const
	{
        METHODNAME_DEF( PXVBOrderEntryParamChecker, checkNarcoticsTransfer )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

		return m_pxOrderEntryParam->IsNarcTransfer();
	}

//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod
