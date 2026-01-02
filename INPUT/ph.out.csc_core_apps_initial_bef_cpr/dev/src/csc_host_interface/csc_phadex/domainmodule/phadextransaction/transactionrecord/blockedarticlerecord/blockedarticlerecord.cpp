#include "blockedarticlerecord.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
BlockedArticleRecord::BlockedArticleRecord( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction )
{
}

BlockedArticleRecord::~BlockedArticleRecord()
{
}

basar::Int16 BlockedArticleRecord::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & BlockedArticleRecord::getCreationDateTime() const
{
	return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 BlockedArticleRecord::getRecordType() const
{
	return TransactionRecordBase::getRecordType();
}

basar::Int32 BlockedArticleRecord::getRecordNo() const
{
	return TransactionRecordBase::getRecordNo();
}

basar::Int32 BlockedArticleRecord::getBlockID() const
{
    return getInt32( 3, 7 ); //size 7
}

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

