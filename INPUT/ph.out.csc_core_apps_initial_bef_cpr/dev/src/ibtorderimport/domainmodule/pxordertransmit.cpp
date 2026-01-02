#include "pxordertransmit.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <misc/metaclassmacro_definitions.h> // libutil
#include <misc/log_macro_definitions.h>      // libutil
#include "exceptions/persistenceexception.h"
#include <ibt/ibtrequest/iibtrequest.h>

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

PxOrderTransmit::PxOrderTransmit(pxSessionInitialization pxSessInit, const log4cplus::Logger& logger) :
	m_Logger(logger)
{
	METHODNAME_DEF( PxOrderTransmit, PxOrderTransmit )
    BLOG_TRACE_METHOD( getLogger(), fun );
	
	m_pxVbPxOrderTransmit = pxVbPxOrderTransmitPtr(new ::pxOrderTransmit(pxSessInit));
}

//-----------------------------------------------------------------------------------------

PxOrderTransmit::~PxOrderTransmit()
{
	METHODNAME_DEF( PxOrderTransmit, ~PxOrderTransmit )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

//-----------------------------------------------------------------------------------------

const log4cplus::Logger& PxOrderTransmit::getLogger()
{
	return m_Logger;
}

//-----------------------------------------------------------------------------------------

void PxOrderTransmit::injectCscDbConnection( libcsc::persistence::ConnectionPtr dbConnection )
{
	m_pxVbPxOrderTransmit->injectDBConnection(dbConnection);
}

//-----------------------------------------------------------------------------------------

void PxOrderTransmit::prepareSession()
{
	METHODNAME_DEF( PxOrderTransmit, prepareSession )
    BLOG_TRACE_METHOD( getLogger(), fun );

	std::stringstream msg;
		
	m_pxVbPxOrderTransmit->prepareSession();

	if( false == m_pxVbPxOrderTransmit->IsGoodState() )
    {
		msg << "NOT GOODSTATE - pxVbOrderTransmit constructed with pxSessionInitialization could not be established" << std::endl;
		msg << "\t\tErrorNumber: " << m_pxVbPxOrderTransmit->ErrorNumber() << " ErrorMsg: " << m_pxVbPxOrderTransmit->ErrorMsg() << std::endl;
		BLOG_ERROR( getLogger(), msg.str());

		throw libcsc::exceptions::PersistenceException( basar::ExceptInfo( "PxOrderTransmit::prepareSession()", "pxVbOrderTransmit is NOT in good state!", __FILE__, __LINE__ ) );
	}
	
	msg << "GOODSTATE - pxVbOrderTransmit constructed with pxSessionInitialization established successfully;" << std::endl;
	BLOG_INFO( getLogger(), msg.str());
}

//-----------------------------------------------------------------------------------------
::pxOrder *  PxOrderTransmit::OrderType(const nString& type, const nString& number,
										const int kommityp,	const int bookingtyp,
										const OriginTypeEnum batchschreiben, const short options,
										const nString& desiredTour, const nDate desiredTourDate)
{
	METHODNAME_DEF( PxOrderTransmit, OrderType )
    BLOG_TRACE_METHOD( getLogger(), fun );

	return m_pxVbPxOrderTransmit->OrderType(type, number, kommityp, bookingtyp, batchschreiben, options, desiredTour, desiredTourDate);
}

//-----------------------------------------------------------------------------------------
::pxOrder*	PxOrderTransmit::OrderTypeNS(const nString& type, const nString& number, const short BranchNo, 
										const int kommityp, const int bookingtyp, 
										const OriginTypeEnum batchschreiben, const short options,
										const nString& desiredTour, const nDate desiredTourDate)
{
	METHODNAME_DEF( PxOrderTransmit, OrderTypeNS )
    BLOG_TRACE_METHOD( getLogger(), fun );

	return m_pxVbPxOrderTransmit->OrderTypeNS(type, number, BranchNo, kommityp, bookingtyp, batchschreiben, options, desiredTour, desiredTourDate);
}

//-------------------------------------------------------------------------------------------------//
bool	PxOrderTransmit::isCustomerLocked(const libcsc::ibt::IIbtRequestPtr ibtRequest)
{
	METHODNAME_DEF( PxOrderTransmit, isCustomerLocked )
    BLOG_TRACE_METHOD( getLogger(), fun );

	bool retVal = false;

	m_pxVbPxOrderTransmit->CustomerId(ibtRequest->getIbtCustomerNo(), ibtRequest->getIbtBranchNo()); // here, IDF + VZ are set to Session / OrderTransmit
			
	if ( false == m_pxVbPxOrderTransmit->IsGoodState() )
	{
		std::stringstream s;
		s << "customer < " << ibtRequest->getIbtCustomerNo() << " >, branch < " << ibtRequest->getIbtBranchNo() << " > locked for order entry!";
		BLOG_WARN(getLogger(), s.str());

		retVal = true;
	}

	return retVal;
}

//-----------------------------------------------------------------------------------------
::pxSession*  PxOrderTransmit::Session()
{
	return m_pxVbPxOrderTransmit->Session();
}

//-----------------------------------------------------------------------------------------
int PxOrderTransmit::End()
{
	METHODNAME_DEF( PxOrderTransmit, End )
    BLOG_TRACE_METHOD( getLogger(), fun );

	return m_pxVbPxOrderTransmit->End();
}
    
//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------
