#include "blockedarticleuc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <document/componentmanager/documentcomponentmanager.h>

#include <blockedarticles/componentmanager/blockedarticlescomponentmanagerptr.h>
#include <blockedarticles/componentmanager/blockedarticlescomponentmanager.h>
#include "blockedarticles/blockedarticles.h"
#include "blockedarticles/blockedarticlesrepository.h"
#include "blockedarticles/blockedarticlesrepositoryptr.h"
#include <domainmodule/phadextransaction/transactionrecord/blockedarticlerecord/iblockedarticlerecord.h>
#include <exceptions/cscexceptionbase.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_logging.h>
#include <libutil/util.h>
#include <pxxmit.hpp>
#include "pxartbaseptr.h"
#include "pxstockbooking.hpp"
#include <pxartbas.hpp>


namespace csc_phadex {
namespace useCase {


BlockedArticleUC::BlockedArticleUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF(BlockedArticleUC, BlockedArticleUC);
    BLOG_TRACE_METHOD( m_Logger, fun );
}

BlockedArticleUC::~BlockedArticleUC()
{
    METHODNAME_DEF(BlockedArticleUC, ~BlockedArticleUC);
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void BlockedArticleUC::setBlockedArticleRecord(csc_phadex::domMod::phadexTransaction::IBlockedArticleRecordPtr dncr )
{
    m_BlockedArticleRecord = dncr;
}

void BlockedArticleUC::injectPxOrderTransmit( pxOrderTransmitPtr xmit )
{
    m_pxOrderTransmit = xmit;
}

void BlockedArticleUC::run()
{
    METHODNAME_DEF(BlockedArticleUC, run );
    BLOG_TRACE_METHOD( m_Logger, fun );

	libcsc::blockedarticles::IBlockedArticlesRepositoryPtr BlockedArticlesRepository =
		m_pxOrderTransmit->getBlockedArticlesComponentManager()->getBlockedArticlesRepository();

	libcsc::blockedarticles::BlockedArticlesCollectionPtr blockedArticlesList =
		BlockedArticlesRepository->findBlockedArticles(
			m_BlockedArticleRecord->getBranchno(),
			m_BlockedArticleRecord->getBlockID());


	libcsc::blockedarticles::BlockedArticlesComponentManagerPtr comp = m_pxOrderTransmit->getBlockedArticlesComponentManager();
	libcsc::blockedarticles::IBlockedArticlesRepositoryPtr repo = comp->getBlockedArticlesRepository();
	libcsc::blockedarticles::BlockedArticlesCollectionPtr coll = repo->findBlockedArticles(m_BlockedArticleRecord->getBranchno(),m_BlockedArticleRecord->getBlockID());
	libcsc::blockedarticles::BlockedArticlesCollection::iterator it = coll->begin();

	enum ReservationTypeEnum resType = RESTYPE_BLOCKED_AUTOMAT;
	basar::VarString pharmGroup;
	pharmGroup = "AUT";

	for (it = coll->begin();it != coll->end();it++)
	{
		if ((*it)->getProcessedDate() > 0)
		{
			continue;	//bereits verarbeitet
		}

		try
		{
			m_pxOrderTransmit->nDBBeginTransaction(cDBTransRecord);
			pxArtBasePtr artBase = pxArtBasePtr(pxArtBase::CreateArticle(m_pxOrderTransmit.get(),
				(*it)->getArticleNo(),
				(*it)->getBranchNo(),
				cDBGET_FORUPDATE));
			if (artBase->IsGoodState())
			{

				if ((*it)->getBookingType() == ACCOUNT_ADD_QUANTITY)
				{
					m_pxOrderTransmit->getStockBooking()->AddArticleReservation(*artBase, resType, pharmGroup, (*it)->getQuantity());
				}
				else if ((*it)->getBookingType() == ACCOUNT_SUB_QUANTITY)
				{
					m_pxOrderTransmit->getStockBooking()->ReleaseArticleReservation(*artBase, resType, pharmGroup, (*it)->getQuantity());
				}
				else if ((*it)->getBookingType() == ACCOUNT_SET_QUANTITY)
				{
					m_pxOrderTransmit->getStockBooking()->SetAbsoluteArticleReservation(*artBase, resType, pharmGroup, (*it)->getQuantity());
				}
				artBase->Put();

				(*it)->setProcessedDate(basar::cmnutil::DateTime::getCurrent().getDate());
				(*it)->setProcessedTime(basar::cmnutil::DateTime::getCurrent().getTime()/1000);

				repo->saveBlockedArticle((*it));
			}
			m_pxOrderTransmit->nDBCommit(cDBTransRecord);
		}
		catch (const libcsc::exceptions::CSCExceptionBase& e)
		{
			std::stringstream ss;
			ss << "BlockedArticleUC::completeCustomerOrder(): Error during reservation: " << e.reason().c_str();
			BLOG_ERROR(LoggerPool::getLoggerUseCases(), ss.str());
		}

	}

}

} // namespace usecase
} // namespace csc_phadex
