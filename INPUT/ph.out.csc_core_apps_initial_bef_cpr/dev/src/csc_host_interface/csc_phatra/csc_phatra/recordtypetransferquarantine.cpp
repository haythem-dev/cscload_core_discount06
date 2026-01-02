//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeTransferQuarantine
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypetransferquarantine.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include "pvhx01_includes.h"
#include "pxartbaseptr.h"

#include "recordprocesshelper.h"
#include "recordprocesshelperptr.h"
#include "pxstockbooking.hpp"
#include <icsc_logger.h>
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeTransferQuarantine::RecordTypeTransferQuarantine()
{
}

RecordTypeTransferQuarantine::~RecordTypeTransferQuarantine()
{
}

void RecordTypeTransferQuarantine::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeTransferQuarantine::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeTransferQuarantine::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeTransferQuarantine::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeTransferQuarantine::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeTransferQuarantine, process );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

		pxArtBasePtr artBase = pxArtBasePtr( pxArtBase::CreateArticle(	m_PXVBSession->get(),
														record->getArticleNo(),
														record->getBranchNo(),
														cDBGET_FORUPDATE	) );
		if (artBase->IsGoodState())
		{
			pxArtStoreLoc storeLoc(	m_PXVBSession->get(),
									record->getArticleNo(), record->getBranchNo(),
									artBase->LagerBereichNr(),
									artBase->LagerFachNr(),
									cDBGET_FORUPDATE	);

			if (record->getBookingType() == ACCOUNT_ADD_QUANTITY)
			{
				if (m_PXVBSession->get()->getStockBooking()->GetAvailableQtyInStock(*artBase) == 0)
				{
					basar::Date now;

					nDate tmpDate(now.getDate());
					pxStockEntry ste(	m_PXVBSession->get(),
										tmpDate,
										record->getBranchNo(),
										record->getArticleNo()	);
					if (!ste.IsGoodState())
					{
						ste.Put();
					}
				}

				if (storeLoc.IsGoodState())
				{
					storeLoc.AddQuantity( record->getQuantity() );
				}
				m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
			}
			else if (record->getBookingType() == ACCOUNT_SUB_QUANTITY)
			{
				if (storeLoc.IsGoodState())
				{
					storeLoc.SubQuantity( record->getQuantity() );
				}
				m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
			}

			m_RecordProcessHelperPtr->writeNarcTransferEntries(artBase, record);

			if(storeLoc.IsGoodState())
			{
				storeLoc.Put();
			}

			artBase->Put();

			if (artBase->IsGoodState())
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );

				if (record->getBookingType() == ACCOUNT_ADD_QUANTITY)
				{
					if (false == record->hasFollowUpRecord())
					{
						DistributeIncomingGoods(m_PXVBSession->get(), record->getBranchNo(), record->getArticleNo()); //defined in pvhx01_includes.h
					}

                    if (m_PXVBDBConnection->isTransactionActive())
                    {
                        //according to andre egerer commit should be used
                        m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
                        m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - DistributeIncomingGoods left transaction open - comitted", record );
                    }
                    else
                    {
                        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text record process - DistributeIncomingGoods left transaction closed", record );
                    }

        	    }
                record->markAsProcessed();
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback", record );
			}
		}
        else
        {
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - no article data found", record );
        }
	}
	catch( basar::Exception& ex )
	{
		m_CSC_Logger->logBasarException("RecordTypeTransferQuarantine::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeTransferQuarantine::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
