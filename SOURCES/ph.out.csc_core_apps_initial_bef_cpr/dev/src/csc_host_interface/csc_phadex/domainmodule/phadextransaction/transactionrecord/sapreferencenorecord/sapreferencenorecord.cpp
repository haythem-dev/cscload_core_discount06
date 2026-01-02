#include "sapreferencenorecord.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
SAPReferenceNoRecord::SAPReferenceNoRecord( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction ), ISAPReferenceNoRecord()
{
}

SAPReferenceNoRecord::~SAPReferenceNoRecord()
{
}

basar::Int16 SAPReferenceNoRecord::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & SAPReferenceNoRecord::getCreationDateTime() const
{
	return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 SAPReferenceNoRecord::getRecordType() const
{
	return TransactionRecordBase::getRecordType();
}

basar::Int32 SAPReferenceNoRecord::getRecordNo() const
{
	return TransactionRecordBase::getRecordNo();
}

const basar::VarString SAPReferenceNoRecord::getProgramName() const
{
	return getString(3, 6); //size 6
}

basar::Int32 SAPReferenceNoRecord::getCscOrderNo() const
{
	return getInt32( 9, 7 ); //size 6
}

basar::Int32 SAPReferenceNoRecord::getPharmosOrderNo() const
{
	return getInt32(16, 7); //size 7
}


basar::VarString SAPReferenceNoRecord::getSapReferenceNo() const
{
    return getString( 23, 10 ); //size 10
}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

