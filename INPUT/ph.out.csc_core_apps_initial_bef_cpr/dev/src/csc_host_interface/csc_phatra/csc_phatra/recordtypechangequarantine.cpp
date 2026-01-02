//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeQuarantine
 *  \author 
 *  \date   
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypechangequarantine.h"
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

RecordTypeChangeQuarantine::RecordTypeChangeQuarantine()
{
}

RecordTypeChangeQuarantine::~RecordTypeChangeQuarantine()
{
}

void RecordTypeChangeQuarantine::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeChangeQuarantine::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBatch( source->getKbvzBatch() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
		basar::VarString cscOrderNo;
        cscOrderNo.format("%d",source->getKbvzKSCAnr()); 
		target->setCSCOrderNo( cscOrderNo );
		target->setStorageArea( source->getKbvzLgnr() );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeChangeQuarantine::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeChangeQuarantine::doTransform...-text generic exception caught", source );
		//throw;
	}
}

#define PHARMOS_STATUS_NO_CERTIFICATE		"8"
#define PHARMOS_STATUS_TENDER				"7"
#define PHARMOS_STATUS_BATCH_RECALL			"5"
#define PHARMOS_STATUS_NO_PACKAGE_INSERT	"3"
#define PHARMOS_STATUS_BLOCKED_AUTOMAT		"S"
#define PHARMOS_STATUS_FMD_QUARANTINE		"F"


void RecordTypeChangeQuarantine::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeChangeQuarantine, process );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	try
	{
		enum ReservationTypeEnum resType = RESTYPE_UNKNOWN;
		basar::VarString pharmGroup;
		if (record->getStorageArea() == PHARMOS_STATUS_NO_CERTIFICATE)
		{
			resType = RESTYPE_NO_CERTIFICATE;
			pharmGroup = "999";
		}
		else if (record->getStorageArea() == PHARMOS_STATUS_TENDER)
		{
			resType = RESTYPE_TENDER;
			pharmGroup = "TEN";
		}
		else if (record->getStorageArea() == PHARMOS_STATUS_BATCH_RECALL)
		{
			resType = RESTYPE_BATCH_RECALL;
			pharmGroup = "999";
		}
		else if (record->getStorageArea() == PHARMOS_STATUS_NO_PACKAGE_INSERT)
		{
			resType = RESTYPE_NO_PACKAGE_INSERT;
			pharmGroup = "299";
		}
		else if (record->getStorageArea() == PHARMOS_STATUS_BLOCKED_AUTOMAT)
		{
			resType = RESTYPE_BLOCKED_AUTOMAT;
			pharmGroup = "AUT";
		}
		else if (record->getStorageArea() == PHARMOS_STATUS_FMD_QUARANTINE)
		{
			resType = RESTYPE_FMD_QUARANTINE;
			pharmGroup = "FMD";
		}
		else
		{
			resType = RESTYPE_UNKNOWN;
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "Unknown reservation type", record);
		}

		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

		pxArtBasePtr artBase = pxArtBasePtr( pxArtBase::CreateArticle(	m_PXVBSession->get(), 
														record->getArticleNo(),
														record->getBranchNo(),
														cDBGET_FORUPDATE	) );
		if (artBase->IsGoodState())
		{
			if (resType != RESTYPE_UNKNOWN)
			{
				if (record->getBookingType() == ACCOUNT_ADD_QUANTITY)
				{
					m_PXVBSession->get()->getStockBooking()->AddArticleReservation(*artBase, resType, pharmGroup, record->getQuantity());
				}
				else if (record->getBookingType() == ACCOUNT_SUB_QUANTITY)
				{
					m_PXVBSession->get()->getStockBooking()->ReleaseArticleReservation(*artBase, resType, pharmGroup, record->getQuantity());
				}
				else if (record->getBookingType() == ACCOUNT_SET_QUANTITY)
				{
					m_PXVBSession->get()->getStockBooking()->SetAbsoluteArticleReservation(*artBase, resType, pharmGroup, record->getQuantity());
				}
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
		m_CSC_Logger->logBasarException("RecordTypeChangeQuarantine::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeChangeQuarantine::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
