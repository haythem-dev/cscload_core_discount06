//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeNoProcessing
 *  \author Steffen Heinlein
 *  \date   09.01.2014
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypenoprocessing.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include <icsc_logger.h>

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

RecordTypeNoProcessing::RecordTypeNoProcessing()
{
}

RecordTypeNoProcessing::~RecordTypeNoProcessing()
{
}

void RecordTypeNoProcessing::doTransform( const core::TransactionRecordBasePtr /*source*/, core::TransactionRecordBasePtr /*target*/ ) const
{    
}

void RecordTypeNoProcessing::process( const core::TransactionRecordBasePtr record ) const
{	    
	record->markAsProcessed(); // no further processing
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
