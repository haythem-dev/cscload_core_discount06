//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeBatch
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypebatch.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>

#include <icsc_logger.h>

#include "pvhx01_includes.h"
#include "pxarticlecharge.hpp"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeBatch::RecordTypeBatch()
{
}

RecordTypeBatch::~RecordTypeBatch()
{
}

void RecordTypeBatch::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
//		METHODNAME_DEF( RecordTypeBatch, doTransform );	fun;

		target->setBookingType( source->getKbvzBukz() ); 
		target->setArticleNo( source->getKbvzPZN() );
		target->setQuantity( std::abs(source->getKbvzMeng()) );	//! \note store absolute quantity, +/- is triggered by bookingtype (STOCKLEVEL_INCREASE/STOCKLEVEL_DECREASE)
		target->setExpiryDate( libcsc_utils::ConvHelper::getDateFor4DigitsDateMMYY( source->getKbvzVerf() ) );
		basar::VarString batch = source->getKbvzStat() + source->getKbvzET3() + source->getKbvzWber();
		target->setBatch( batch );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeBatch::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeBatch::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeBatch::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeBatch, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

		try
		{
            m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

			pxArticleCharge charge(	m_PXVBSession->get(), record->getBranchNo(), record->getArticleNo(), record->getBatch() );
		
			if( charge.Get( cDBGET_FORUPDATE ) ) // entry not found -> cDBGET_FORUPDATE from database.hpp
			{
				charge.SetStock( record->getQuantity() );

                // handle invalid dates as pvhx01 does
                if (!record->getExpiryDate().isValid())
                {
                    //maps to expdate = 0 in articlecharge
                    charge.SetExpiryDate( basar::Date( core::PXVB_RECORDTYPE_BATCH_INVALID_DATE ) );
                }
                else
                {
					basar::Int32 daysOfMonth = basar::Date::getDaysOfMonth( record->getExpiryDate().getYear(), record->getExpiryDate().getMonth() );
					basar::Date expdate = basar::Date( record->getExpiryDate().getYear(), record->getExpiryDate().getMonth(), daysOfMonth );										
				    charge.SetExpiryDate( expdate );
                }

				charge.SetStateCharge( BATCHSTATUS_SALEABLE );
			}
			else
			{ 		
				if( record->getBookingType() == ACCOUNT_ADD_QUANTITY ) // TODO: Ask the record class
				{
					charge.AddQuantity( record->getQuantity() );
				}
				else if( record->getBookingType() == ACCOUNT_SUB_QUANTITY ) // TODO: Ask the record class
				{
					charge.SubQuantity( record->getQuantity() );
				}
                //added to pvhx01 on 03.12.12
                // handle invalid dates as pvhx01 does
                //changed on 21.12.12 - only update if record's date is valid
                if (record->getExpiryDate().isValid())
                {
					basar::Int32 daysOfMonth = basar::Date::getDaysOfMonth( record->getExpiryDate().getYear(), record->getExpiryDate().getMonth() );
					basar::Date expdate = basar::Date( record->getExpiryDate().getYear(), record->getExpiryDate().getMonth(), daysOfMonth );										
				    charge.SetExpiryDate( expdate );				    

                    charge.SetStateCharge( BATCHSTATUS_SALEABLE );
                }
				
                //end add
			}
			
            charge.Put();
			if( charge.IsGoodState() )
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
                record->markAsProcessed();
			}
			else 
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - charge put failed", record );
			}
		}
		catch( basar::Exception& /*ex*/ )
		{
			// TODO Alerting, Mailing, Exception-Handling! Es muß hier sofort reagiert werden! Daten zum Record mit ausgeben!!!
			m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "RecordTypeBatch::process-text basar exception caught", record );
			//throw;
		}
		catch( ... )
		{
			// TODO Alerting, Mailing, Exception-Handling! Es muß hier sofort reagiert werden! Daten zum Record mit ausgeben!!!
			m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "RecordTypeBatch::process...-text generic exception", record );
			//throw;
		}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
