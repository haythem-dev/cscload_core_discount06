//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypePickingLack
 *  \author Steffen Heinlein
 *  \date   09.01.2014
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypepickinglack.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"

#include "recordprocesshelper.h"

#include <icsc_logger.h>
#include <convhelper.h>

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

RecordTypePickingLack::RecordTypePickingLack()
{
}

RecordTypePickingLack::~RecordTypePickingLack()
{
}

void RecordTypePickingLack::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypePickingLack::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
    METHODNAME_DEF( RecordTypePickingLack, doTransform );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	try
	{		
		target->setBookingType( source->getKbvzBukz() );
		target->setArticleNo( source->getKbvzPZN() );
		target->setQuantity( std::abs(source->getKbvzMeng()) );	//! \note store absolute quantity, +/- is triggered by record type)

		basar::VarString cscOrderNo;
        cscOrderNo.format("%d",source->getKbvzKSCAnr()); 
		target->setCSCOrderNo( cscOrderNo );
		
		libcsc_utils::TimeParts time = libcsc_utils::ConvHelper::getTimeParts4NumericTime( source->getKbvzTime() );
		basar::Date date = libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzDate() );
		basar::DateTime datetime;
		datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
		datetime.setTime( time.m_Hour, time.m_Minute, time.m_Second );
		target->setInvoiceDateTime( datetime );		

		// just for information
		target->setBatch( source->getKbvzET3() );		
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypePickingLack::doTransform-text basar exception caught", ex, source);
    }
	catch(...)
	{
		m_CSC_Logger->logGenericException("RecordTypePickingLack::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypePickingLack::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypePickingLack, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		basar::Int32 quantity = record->getQuantity();

		// 21.01.2014: Vorgabe von A.Egerer: vorerst nur Änderung Menge geliefert in kdauftragpos!
		pxOrder order( m_PXVBSession->get(), record->getCSCOrderNo().stol(), cDBGET_READONLY );
		if( order.IsGoodState() )
		{
			pxOrderItemList* oilist = order.ItemList();		
			if( oilist->Entries() > 0 )
			{	
				pxOrderItemListIter iter = pxOrderItemListIter( *oilist );
				pxOrderItem* orderitem;
				while( NULL != (orderitem = static_cast<pxOrderItem*>(++iter)) )
				{
					if( orderitem )			
					{
						if( record->getArticleNo() == orderitem->ArtikelNr() )
						{
							m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );
							orderitem->Get( cDBGET_FORUPDATE );		
							if( record->getBookingType() == ACCOUNT_ADD_QUANTITY ) // Defekt bei Kommissionierung
							{					
								if( orderitem->MengeGeliefert() < quantity )
								{
									quantity = quantity - orderitem->MengeGeliefert();
									orderitem->MengeGeliefert( 0 );
								}
								else
								{
									orderitem->MengeGeliefert( orderitem->MengeGeliefert() - quantity );
									quantity = 0;
								}
							}
							else if( record->getBookingType() == ACCOUNT_SUB_QUANTITY ) // Mengenerhöhung bei Kommissionierung
							{
								orderitem->MengeGeliefert( orderitem->MengeGeliefert() + record->getQuantity() );
								quantity = 0;
							}										
							orderitem->Put();					
							if( !orderitem->IsGoodState() )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "KD: pxOrderItem could not be saved", record );						
							}										
							m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
						}
					}

					if( 0 == quantity )
					{
						break;
					}
				}

				/*
				pxOrderItem* orderitem = oilist->FindItemByArticleNo( record->getArticleNo() );				
				if( orderitem )			
				{
					m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );
					orderitem->Get( cDBGET_FORUPDATE );		
					if( record->getBookingType() == ACCOUNT_ADD_QUANTITY ) // Defekt bei Kommissionierung
					{					
						orderitem->MengeGeliefert( orderitem->MengeGeliefert() - record->getQuantity() );
					}
					else if( record->getBookingType() == ACCOUNT_SUB_QUANTITY ) // Mengenerhöhung bei Kommissionierung
					{
						orderitem->MengeGeliefert( orderitem->MengeGeliefert() + record->getQuantity() );
					}										
					orderitem->Put();					
					if( !orderitem->IsGoodState() )
					{
						m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "KD: pxOrderItem could not be saved", record );						
					}										
					m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
				}
				*/
			}				
		}			

		// update tender progress
		m_RecordProcessHelperPtr->updateTenderProgress( record );				

		record->markAsProcessed(); 		
	}
	catch( basar::Exception& ex )
	{		
		m_CSC_Logger->logBasarException("RecordTypePickingLack::process : text basar exception caught", ex, record );		
	}
	catch( ... )
	{		
		m_CSC_Logger->logGenericException("RecordTypePickingLack::process... : text generic exception caught", record );		
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
