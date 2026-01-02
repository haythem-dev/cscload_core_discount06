    //----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeBase
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypebase.h"
#include "transactionrecordbase.h"
#include "pharmostransactionrecord.h"

#include <icsc_logger.h>
#include "pxvbdbconnection.h"
#include "pxvbsession.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{

RecordTypeBase::RecordTypeBase()
{
}

RecordTypeBase::~RecordTypeBase()
{
}

void RecordTypeBase::injectCSC_Logger( libcsc_utils::ICSC_LoggerPtr csc_logger)
{
	m_CSC_Logger = csc_logger;
}

void RecordTypeBase::injectPXVBDBConnection( pxVerbund::IPXVBDBConnectionPtr conn )
{
	m_PXVBDBConnection = conn;		
}

void RecordTypeBase::injectPXVBSession( pxVerbund::IPXVBSessionPtr sess )
{
	m_PXVBSession = sess;
}

void RecordTypeBase::transform( const TransactionRecordBasePtr source, TransactionRecordBasePtr target ) const
{
	try
	{
		// common transforms	
		target->setBranchNo( source->getKbvzFil() );
		target->setVSEOffset( source->getKbvzOffset() );
		target->setDatasetSequenceNo( source->getKbvzLfdNr() );
		target->setRecordType( source->getType() );	
		target->setCreationDateTime( basar::DateTime::getCurrent() );		// -> CreationDateTime  ist Zeitpunkt wann der Satz in IFX-Tabelle geschrieben wurde	
		target->setTransferredTimestamp( source->getKbvzDX01DateTime() );	// -> TransferredTimeStamp ist Zeitpunkt wann von DEBVZ in DKBVZ übertragen wurde			
		target->setDailyClosing( source->getKbvzDailyClosing() );			// -> DailyClosing ist Datum des letzten Tagesabschluß der in PDX100 im TA in PA11 geschrieben wird
		target->setOrigin( PharmosTransactionRecord::Origin::PHARMOS ); 	// -> Source default PHARMOS, overwritten by ZDP Recordtypes
		target->setStorageArea(source->getKbvzLgnr());

		// specific transforms 
		doTransform( source, target );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeBase::transform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeBase::transform...-text generic exception caught", source );
	}
}

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod
