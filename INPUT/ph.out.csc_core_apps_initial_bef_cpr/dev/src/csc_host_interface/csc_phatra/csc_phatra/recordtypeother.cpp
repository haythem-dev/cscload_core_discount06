//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeOther
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypeother.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include "pvhx01_includes.h"
#include "pxartbaseptr.h"

#include <icsc_logger.h>

#include "recordprocesshelper.h"
#include "recordprocesshelperptr.h"
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeOther::RecordTypeOther()
{
}

RecordTypeOther::~RecordTypeOther()
{
}

void RecordTypeOther::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeOther::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeOther::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeOther::doTransform...-text generic exception", source );
		//throw;
	}
}

void RecordTypeOther::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeOther, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

        pxArtBasePtr artBase = pxArtBasePtr(pxArtBase::CreateArticle( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), cDBGET_FORUPDATE));

        if (artBase->IsGoodState())
        {
            pxArtStoreLoc artStoreLoc( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), artBase->LagerBereichNr(), artBase->LagerFachNr(), cDBGET_FORUPDATE);

		    if (record->getBookingType() == ACCOUNT_ADD_QUANTITY)
		    {
			    if (artStoreLoc.IsGoodState())
			    {
				    artStoreLoc.AddQuantity( record->getQuantity() );
			    }
                else
                {
                    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text artStoreLoc is not in good state - normal here", record );
                }

			    m_RecordProcessHelperPtr->calcArtBaseStock(artBase, record);
		    }
		    else if( record->getBookingType() == ACCOUNT_SUB_QUANTITY)
		    {
			    if (artStoreLoc.IsGoodState())
			    {
				    artStoreLoc.SubQuantity( record->getQuantity() );
			    }
                else
                {
                    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text artStoreLoc is not in good state - normal here", record );
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
                else
                {
                    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text artStoreLoc is not in good state - normal here", record );
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
                    else
                    {
                        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text stockRev is not in good state - normal here", record );
                    }
			    }
		    }
		    else
		    {
			    m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text unknown booking type", record ); //remove it? not all "other" record types have a valid booking type
		    }

			m_RecordProcessHelperPtr->writeNarcTransferEntries(artBase, record);

		    if (artStoreLoc.IsGoodState())
		    {
			    artStoreLoc.Put();
		    }
		    else
		    {
			    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text artStoreLoc not saved - normal here", record );
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

		    if ( record->getType() == "BO" || (record->getType() == "LR" && record->getBookingType() == ACCOUNT_ADD_QUANTITY))
		    {
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
        }
        else
        {
			m_PXVBDBConnection->rollbackTransaction();
            m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process record type other, skipped record - artBase not good", record );
        }
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeOther::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeOther::process...-text generic exception", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
