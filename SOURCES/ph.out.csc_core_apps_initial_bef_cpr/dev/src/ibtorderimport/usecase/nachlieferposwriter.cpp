/*#include "nachlieferposwriter.h"
#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtresponse/iibtresponse.h>
#include <exceptions/persistenceexception.h>
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <libbasarcmnutil.h>

#include <pxorder.hpp>



namespace ibtorderimport
{
namespace useCase
{

	using pxVerbund::subsequentDelivery::pxDeliveryPos;


NachlieferPosWriter::NachlieferPosWriter()
{
}

NachlieferPosWriter::~NachlieferPosWriter()
{
}

void NachlieferPosWriter::save( libcsc::ibt::IIbtRequestPtr ibtRequest, libcsc::ibt::IIbtResponsePtr ibtResponse, pxOrderItem * orderItem )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerUseCases(), "NachlieferPosWriter::save()" );
	
	// insert nachlieferpos (= ibtresponse)
	if( 0 == ibtResponse->getIbtOrderPosNo() )
	{
		return;
	}

	BLOG_DEBUG( LoggerPool::getLoggerUseCases(), "inserting nachlieferpos..." );

	// Construct	NachLieferPos by copying from pxOrderItem
	pxDeliveryPos sdPos( *orderItem, pxVerbund::subsequentDelivery::pxDPT_BATCH_ITEM );
	sdPos.SetIDFNr( ibtRequest->getCustomerNo() );
	sdPos.SetFirstPartnerNr( ibtRequest->getBranchNo() );
	sdPos.SetSecondPartnerNr( 0 );
	sdPos.SetThirdPartnerNr( 0 );
	sdPos.SetUrsprungAuftragNr( ibtRequest->getCscOrderNo() );
	sdPos.SetUrsprungPosNr( ibtRequest->getCscOrderPosNo() );
	sdPos.Put();

	if( false == sdPos.IsGoodState() )
	{
		throw libcsc::exceptions::PersistenceException( basar::ExceptInfo( "NachlieferPosWriter::save()", "::pxDeliveryPos NOT in GoodState!", __FILE__, __LINE__ ) );
		// -329 articlecode = NULL wenn Item.confirmedqty = 0 !
	}

	BLOG_DEBUG( LoggerPool::getLoggerUseCases(), "nachlieferpos written." );
}

} // namespace usecase
}*/ // namespace ibtorderimport
