//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeIBTStockLevel
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypechangeibtstocklevel.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include <icsc_logger.h>

#include "pvhx01_includes.h"
#include "pxartstorelocptr.h"
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

    struct null_deleter
    {
        void operator()(void const *) const
        {
        }
    };

RecordTypeChangeIBTStockLevel::RecordTypeChangeIBTStockLevel()
{
}

RecordTypeChangeIBTStockLevel::~RecordTypeChangeIBTStockLevel()
{
}

void RecordTypeChangeIBTStockLevel::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );
		target->setIbtBranchNo( source->getKbvzMFil() ); 
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeChangeIBTStockLevel::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeChangeIBTStockLevel::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeChangeIBTStockLevel::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeChangeIBTStockLevel, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

		pxArtStoreLocList artStoreLocList( m_PXVBSession->get() );
		artStoreLocList.Select( record->getArticleNo(), record->getIbtBranchNo() );
		
		pxArtStoreLocPtr artStoreLoc;
		if ( (artStoreLoc = pxArtStoreLocPtr(artStoreLocList.Find(record->getIbtBranchNo()), null_deleter() ) ) ) //method returns pointer
		{
			if ( artStoreLoc->Get( cDBGET_FORUPDATE ) == 0 )
			{
				if ( record->getBookingType() == ACCOUNT_ADD_QUANTITY )
				{
					artStoreLoc->AddQuantity( record->getQuantity() );
				}
				else if ( record->getBookingType() == ACCOUNT_SUB_QUANTITY ) 
				{
					artStoreLoc->SetQuantity( static_cast<basar::BLong>(0) );
				}
				else if ( record->getBookingType() == ACCOUNT_SET_QUANTITY )
				{
					artStoreLoc->SetQuantity( record->getQuantity() );
				}

				artStoreLoc->Put();

				if (artStoreLoc->IsGoodState())
				{
					m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
                    record->markAsProcessed();
				}
				else
				{
					m_PXVBDBConnection->rollbackTransaction();
					m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artStoreLoc put failed", record );
				}
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artStoreLoc failed get for update", record );
			}
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - no artstoreloc", record );
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeChangeIBTStockLevel::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeChangeIBTStockLevel::process...-text generic exception caught", record );
		//throw;
	}
	/*
								stl = new pxArtStoreLocList(xmit->Session());	
								stl->Select(ArtikelNr,MFilialNr);
								if ( storeloc = stl->Find(MFilialNr) )
								{
									if ( storeloc->Get(cDBGET_FORUPDATE) == 0)
									{
										if (Buchung == cACCOUNT_ADD) { storeloc->AddQuantity(Menge); }
										else if (Buchung == cACCOUNT_SUB) { storeloc->SetQuantity(0L); }
										else if (Buchung == cACCOUNT_SET) { storeloc->SetQuantity(Menge); }
										storeloc->Put();
									}
								}
								delete stl;
								storeloc = NULL;
	*/
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod