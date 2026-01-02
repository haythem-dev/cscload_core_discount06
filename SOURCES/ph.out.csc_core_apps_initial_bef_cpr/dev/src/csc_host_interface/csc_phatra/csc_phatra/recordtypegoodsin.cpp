//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeGoodsIn
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypegoodsin.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include "pvhx01_includes.h"
#include "pxartbaseptr.h"

#include <icsc_logger.h>

#include "recordprocesshelper.h"
#include "recordprocesshelperptr.h"
#include "pxstockbooking.hpp"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeGoodsIn::RecordTypeGoodsIn()
{
}

RecordTypeGoodsIn::~RecordTypeGoodsIn()
{
}

void RecordTypeGoodsIn::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeGoodsIn::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{

	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
		target->setBatch( source->getKbvzBatch().substr(0, 24) ); //set anyway - works b/c 1st param is 0
		target->setOrderSupplierNo( source->getKbvzBeslaNr() );

		if ( !(source->getKbvzET3().empty()) )
		{
			basar::VarString supplierno = source->getKbvzET3().substr(8,5);	//will not work on empty string
			supplierno.trim(basar::cmnutil::BString::FIRST_END);
			target->setSupplierNo( supplierno.stoi() );

			basar::VarString purchaseorderno = source->getKbvzET3().substr(0,7);
			purchaseorderno.trim(basar::cmnutil::BString::FIRST_END);
			target->setPurchaseOrderNo( purchaseorderno );
		}
		else
		{
		        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text record transform - KbvzET3 was empty string", source );
		}

	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeGoodsIn::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeGoodsIn::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeGoodsIn::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeGoodsIn, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

		pxArtBasePtr artBase = pxArtBasePtr (pxArtBase::CreateArticle(	m_PXVBSession->get(),
														record->getArticleNo(),
														record->getBranchNo(),
														cDBGET_FORUPDATE	) );
		if (artBase->IsGoodState())
		{
			if (record->getBookingType() == ACCOUNT_ADD_QUANTITY)
			{
				if (m_PXVBSession->get()->getStockBooking()->GetAvailableQtyInStock(*artBase) == 0)
				{
					basar::Date now;
					nDate tmpDate(now.getDate());
					pxStockEntry ste(	m_PXVBSession->get(), tmpDate,	record->getBranchNo(), record->getArticleNo()	);
					if (!ste.IsGoodState())
					{
						ste.Put();
					}
				}
				pxArtStoreLoc storeloc(	m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), artBase->LagerBereichNr(),	artBase->LagerFachNr(),	cDBGET_FORUPDATE );
				if (storeloc.IsGoodState())
				{
					storeloc.AddQuantity( record->getQuantity() );
					storeloc.Put();
				}
				m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
				m_RecordProcessHelperPtr->writeNarcTransferEntries(artBase, record);
			}
			if (record->getBookingType() == CERTIFICATE_AVAILABLE ||  record->getBookingType() == CERTIFICATE_NOT_AVAILABLE || record->getBookingType() == CERTIFICATE_UPDATE || record->getBookingType() == PACKAGE_INSERT_NOT_AVAILABLE)
			{
				m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
			}
			if (record->getBookingType() == BATCH_RECALL)
			{
				m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
				m_RecordProcessHelperPtr->changeBatchSaleability(artBase, record);

			}
			if (record->getBookingType() == CANCEL_BATCH_RECALL)
			{
				m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
				m_RecordProcessHelperPtr->changeBatchSaleability(artBase, record);
			}
			artBase->Put();
			if (artBase->IsGoodState())
			{
                m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );

				if (false == record->hasFollowUpRecord())
				{
					DistributeIncomingGoods(m_PXVBSession->get(), record->getBranchNo(), record->getArticleNo()); //defined in pvhx01_includes.h
				}
                if (m_PXVBDBConnection->isTransactionActive())
                {
                    //according to andre egerer commit should be used
                    m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
					m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text record process pxverbund rollback - DistributeIncomingGoods left transaction open - comitted", record );
                }
                else
                {
                    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text record process - DistributeIncomingGoods left transaction closed", record );
                }

                record->markAsProcessed();
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artBase put failed", record );
			}
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
            m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "text record process no article found", record );
            //should we throw here? for we couldn't create an article...
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO Alerting, Mailing, Exception-Handling! Es muß hier sofort reagiert werden! Daten zum Record mit ausgeben!!!
		m_CSC_Logger->logBasarException("RecordTypeGoodsIn::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO Alerting, Mailing, Exception-Handling! Es muß hier sofort reagiert werden! Daten zum Record mit ausgeben!!!
		m_CSC_Logger->logGenericException("RecordTypeGoodsIn::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
