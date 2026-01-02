//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeArticleInfoGoodsIn
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypearticleinfogoodsin.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeArticleInfoGoodsIn::RecordTypeArticleInfoGoodsIn()
{
}

RecordTypeArticleInfoGoodsIn::~RecordTypeArticleInfoGoodsIn()
{
}

void RecordTypeArticleInfoGoodsIn::doTransform( const core::TransactionRecordBasePtr, core::TransactionRecordBasePtr ) const
{	
	// no values needed	
}

void RecordTypeArticleInfoGoodsIn::process( const core::TransactionRecordBasePtr record) const
{	
	// no processing
    record->markAsProcessed();
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod