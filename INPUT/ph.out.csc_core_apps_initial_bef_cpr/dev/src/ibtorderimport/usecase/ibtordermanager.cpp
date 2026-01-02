#include "ibtordermanager.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <misc/metaclassmacro_definitions.h> // libutil
#include <misc/log_macro_definitions.h>      // libutil
#include "domainmodule/ipxordertransmit.h"
#include <ibt/ibtrequest/iibtrequest.h>
#include "domainmodule/ipxorder.h"
#include "domainmodule/pxorder.h"
#include <ibt/ibtrequest/ibtrequest.h>
#include "types/origintypeenum.inc"
#include "domainmodule/pxvb_includes.h"

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace useCase {

//-----------------------------------------------------------------------------------------

IbtOrderManager::IbtOrderManager(const log4cplus::Logger& logger) :
	m_Logger(logger)
{
	METHODNAME_DEF( IbtOrderManager, IbtOrderManager )
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-----------------------------------------------------------------------------------------

IbtOrderManager::~IbtOrderManager()
{
	METHODNAME_DEF( IbtOrderManager, ~IbtOrderManager )
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-----------------------------------------------------------------------------------------

void IbtOrderManager::save()
{
	METHODNAME_DEF( IbtOrderManager, save )
	BLOG_TRACE_METHOD( getLogger(), fun );

	BLOG_DEBUG(getLogger(), "saving pxOrder and all connected pxOrderItems ...");

	// dadurch werden sowohl Kopf als auch zugehörige Items gespeichert!
	getPxOrderTransmit()->End();
}

//-----------------------------------------------------------------------------------------

domMod::IPxOrderPtr IbtOrderManager::getOrder( libcsc::ibt::IIbtRequestPtr ibtRequest )
{
	METHODNAME_DEF( IbtOrderManager, getOrder )
	BLOG_TRACE_METHOD( getLogger(), fun );

	domMod::IPxOrderPtr order;
	// take desired tour from ibtrequest (new fields: ibttourid + ibttourdate)
	basar::VarString ibtTour = ibtRequest->getIbtTourId();
	basar::Date ibtTourDate  = ibtRequest->getIbtTourDate();

	// OrderType(NS) ==> Suche nach existierendem Auftrag zu IDF, VZ, Auftragsart, Kommiart, Buchungsart, Tour
	if (getPxOrderTransmit()->Session()->getOrderEntryParam(ibtRequest->getIbtBranchNo())->IsNewSuivra()) // new Suivra
	{
		order = domMod::IPxOrderPtr( new domMod::PxOrder(getLogger(), getPxOrderTransmit()->OrderTypeNS(	
																					basar::VarString(ibtRequest->getOrderType()).c_str(), 
																					"0", 
																					ibtRequest->getBranchNo(), // HerkunftFiliale
																					basar::VarString(ibtRequest->getPickingType()).stoi(), 
																					basar::VarString(ibtRequest->getBookingType()).stoi(), 
																					cORTYPE_AUXILIARY,
																					0, // options
																					ibtTour.c_str(),
																					ibtTourDate.getDate())));

		order->markAsNewSuivra();
	}
	else
	{
		if (false == TourManager::checkIsTourValid(getPxOrderTransmit()->Session(), ibtRequest->getIbtBranchNo(), ibtRequest->getIbtCustomerNo(), ibtTour.c_str(), ibtTourDate.getDate())) // --> desired tour is not valid !
		{
			////möglicherweise obsolet, sollte pxVerbund machen
			// find next valid tour (+ date) for this article
			TourInfo tourInfo = TourManager::getCustomerTourForArticle(getPxOrderTransmit()->Session(), ibtRequest->getIbtBranchNo(), ibtRequest->getIbtCustomerNo(), ibtRequest->getArticleNo());

			// log, dass desired tour "invalid" und daher übersteuert wurde
			std::stringstream s;
			s << "Invalid desired tour < " << ibtTour.c_str() << " >, date < " << ibtTourDate.getDate() << " > of ibt request < " << ibtRequest->getIbtRequestId() << " > overwritten by new tour value < " <<
				tourInfo.getTourID() << ", " << tourInfo.getTourDate().GetYYYYMMDD() << " >.";
			BLOG_WARN(getLogger(), s.str());

			// only take next valid tour, if desired tour is not valid anymore
			ibtTour = basar::VarString(tourInfo.getTourID());
			ibtTourDate = tourInfo.getTourDate().GetYYYYMMDD();
		}

		order = domMod::IPxOrderPtr( new domMod::PxOrder(getLogger(), getPxOrderTransmit()->OrderType(	
																					basar::VarString(ibtRequest->getOrderType()).c_str(), 
																					"0", 
																					basar::VarString(ibtRequest->getPickingType()).stoi(), 
																					basar::VarString(ibtRequest->getBookingType()).stoi(), 
																					cORTYPE_AUXILIARY,
																					0, // options
																					ibtTour.c_str(),
																					ibtTourDate.getDate())));
	}

	std::stringstream s;
	s << "pxOrder < " << order->getOrderNo() << " > created.";
	BLOG_DEBUG(getLogger(), s.str());

	// warum nochmal???
	order->setOrderType(ibtRequest);

	order->setPaymentTerm(ibtRequest->getPaymentTerm());
	
	order->determineIbtComment();

	order->setOriginBranchNo(ibtRequest->getBranchNo());

	if (false == order->isBatchWriting())
		order->activateBatchWriting();
	
	return order;
}

//-----------------------------------------------------------------------------------------

void IbtOrderManager::injectPxOrderTransmit(domMod::IPxOrderTransmitPtr pxOrderTransmit)
{
	m_PxOrderTransmit = pxOrderTransmit;
}

//-----------------------------------------------------------------------------------------

domMod::IPxOrderTransmitPtr IbtOrderManager::getPxOrderTransmit()
{
	return m_PxOrderTransmit;
}

//-----------------------------------------------------------------------------------------
const log4cplus::Logger& IbtOrderManager::getLogger()
{
	return m_Logger;
}

//-----------------------------------------------------------------------------------------

} // namespace useCase
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------
