//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeExpiryDate
 *  \author Steffen Heinlein
 *  \date   06.03.2013
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypeexpirydate.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>
#include <icsc_logger.h>
#include "pxartbaseptr.h"
#include "pvhx01_includes.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeExpiryDate::RecordTypeExpiryDate()
{
}

RecordTypeExpiryDate::~RecordTypeExpiryDate()
{
}

void RecordTypeExpiryDate::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
						        
		basar::Date expdate;
		if( core::PXVB_RECORDTYPE_EXPIRYDATE_INVALID_MINDATE == source->getKbvzVerf() )
		{
			expdate = core::PXVB_RECORDTYPE_EXPIRYDATE_MINDATE;
		}
		else if( core::PXVB_RECORDTYPE_EXPIRYDATE_INVALID_MAXDATE == source->getKbvzVerf() )
		{
			expdate = core::PXVB_RECORDTYPE_EXPIRYDATE_MAXDATE;
		}
		else
		{
			expdate = libcsc_utils::ConvHelper::getDateFor4DigitsDateMMYY( source->getKbvzVerf() );
		}
		target->setExpiryDate( expdate );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeExpiryDate::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeExpiryDate::doTransform...-text generic exception caught", source );		
	}
}

void RecordTypeExpiryDate::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeExpiryDate, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );
		pxArtBasePtr artBase = pxArtBasePtr(pxArtBase::CreateArticle( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), cDBGET_FORUPDATE) );
		if ( artBase->IsGoodState() )	
		{
			pxArtStoreLoc artStoreLoc( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), artBase->LagerBereichNr(), artBase->LagerFachNr(), cDBGET_FORUPDATE);
			if (artStoreLoc.IsGoodState())
			{
				if( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MINDATE == record->getExpiryDate() )
				{
					artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MINDATE ); 
				}
				else if( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MAXDATE == record->getExpiryDate() )
				{
					artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MAXDATE ); 
				}
				else if( !record->getExpiryDate().isValid() )
				{
					artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_DATE ); 
				}
				else
				{
					artStoreLoc.DatumVerfall( libcsc_utils::ConvHelper::get4DigitsDateYYMMFromDate(record->getExpiryDate()) ); 
				}

				artStoreLoc.Put();
				if ( !artStoreLoc.IsGoodState() )
				{
					//todo: logging
					m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "VD: text save artStoreLoc failed", record );
				}				
			}

			if ( !artBase->IsGoodState() )
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "VD text record process pxverbund rollback - artBase not in good state", record );
			}
			else
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
                record->markAsProcessed();
			}			
		}
		else
        {
            m_PXVBDBConnection->rollbackTransaction();
        }
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeExpiryDate::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeExpiryDate::process...-text generic exception", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod