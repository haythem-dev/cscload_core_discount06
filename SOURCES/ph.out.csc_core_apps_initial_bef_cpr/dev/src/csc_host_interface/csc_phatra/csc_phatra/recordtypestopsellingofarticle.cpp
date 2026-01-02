//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeStopSellingOfArticle
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypestopsellingofarticle.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

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

RecordTypeStopSellingOfArticle::RecordTypeStopSellingOfArticle()
{
}

RecordTypeStopSellingOfArticle::~RecordTypeStopSellingOfArticle()
{
}

void RecordTypeStopSellingOfArticle::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeStopSellingOfArticle::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeStopSellingOfArticle::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeStopSellingOfArticle::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeStopSellingOfArticle, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

		pxArtBasePtr artBase = pxArtBasePtr (pxArtBase::CreateArticle(	m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), cDBGET_FORUPDATE));

		if (artBase->IsGoodState())
		{
			artBase->SetNotSaleable();

			artBase->Put();

			if (artBase->IsGoodState())
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
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
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artBase not in good state", record );
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeStopSellingOfArticle::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeStopSellingOfArticle::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod