//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCodeBlocage
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecodeblocage.h"
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

RecordTypeCodeBlocage::RecordTypeCodeBlocage()
{
}

RecordTypeCodeBlocage::~RecordTypeCodeBlocage()
{
}

void RecordTypeCodeBlocage::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeCodeBlocage::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
		target->setCodeBlocage( source->getKbvzStat() );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeCodeBlocage::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeCodeBlocage::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeCodeBlocage::process( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCodeBlocage, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

		pxArtBasePtr artBase = pxArtBasePtr(pxArtBase::CreateArticle( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), cDBGET_FORUPDATE ) );

		if (artBase->IsGoodState())
		{
			artBase->CheckCodeBlocage( (record->getCodeBlocage())[0] );
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
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeCodeBlocage::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeCodeBlocage::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
