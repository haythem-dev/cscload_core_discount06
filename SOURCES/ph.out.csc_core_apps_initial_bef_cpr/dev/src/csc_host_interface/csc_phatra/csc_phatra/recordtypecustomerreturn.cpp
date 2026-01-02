//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeCustomerReturn
 *  \author Steffen Heinlein
 *  \date   09.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecustomerreturn.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include "recordprocesshelper.h"
#include "recordprocesshelperptr.h"

#include <icsc_logger.h>

#include "pvhx01_includes.h"
#include "pxartbaseptr.h"
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeCustomerReturn::RecordTypeCustomerReturn()
{
}

RecordTypeCustomerReturn::~RecordTypeCustomerReturn()
{
}

void RecordTypeCustomerReturn::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeCustomerReturn::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );

		basar::VarString customer = source->getKbvzET3();
		customer = customer.substr( 0, 7 );
		target->setCustomerNo( customer );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeCustomerReturn::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeCustomerReturn::doTransform...-text generic exception", source );
		//throw;
	}
}

void RecordTypeCustomerReturn::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeCustomerReturn, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

        pxArtBasePtr artBase = pxArtBasePtr(pxArtBase::CreateArticle( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), cDBGET_FORUPDATE ));

		pxArtStoreLoc artStoreLoc( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), artBase->LagerBereichNr(), artBase->LagerFachNr(), cDBGET_FORUPDATE);

		if (record->getBookingType() == ACCOUNT_ADD_QUANTITY)
		{
			if (artStoreLoc.IsGoodState())
			{
				artStoreLoc.AddQuantity( record->getQuantity() );
			}

			m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
		}
		else if( record->getBookingType() == ACCOUNT_SUB_QUANTITY)
		{
			if (artStoreLoc.IsGoodState())
			{
				artStoreLoc.SubQuantity( record->getQuantity() );
			}
			m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
		}
		else if( record->getBookingType() == ACCOUNT_SET_QUANTITY )
		{
			basar::BLong quantityToSet = record->getQuantity();

			if ( quantityToSet < 0 )
			{
				quantityToSet = 0;
			}

			if (artStoreLoc.IsGoodState())
			{
				artStoreLoc.SetQuantity(quantityToSet);
			}

			m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);

			if ( artBase->IsStopSelling() )
			{
				pxStockRev stockRev( m_PXVBSession->get(), record->getBranchNo(), record->getArticleNo());
				if( stockRev.IsGoodState() )
				{
					stockRev.Delete();
					artBase->ReleaseStopSelling();
				}
			}
		}
		else
		{
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text unknown booking type", record );
		}

		m_RecordProcessHelperPtr->writeNarcTransferEntries(artBase, record);

		if (artStoreLoc.IsGoodState())
		{
			artStoreLoc.Put();
		}
		else
		{
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text artStoreLoc not saved", record );
		}

        artBase->Put();

		if (artBase->IsGoodState())
		{
			m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
            record->markAsProcessed();
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artBase put failed", record );
		}


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

	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeCustomerReturn::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeCustomerReturn::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
