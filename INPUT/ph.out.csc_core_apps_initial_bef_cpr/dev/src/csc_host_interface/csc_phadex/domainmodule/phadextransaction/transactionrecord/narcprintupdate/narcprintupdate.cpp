#include "narcprintupdate.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
NarcPrintUpdate::NarcPrintUpdate( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction )
{
}

NarcPrintUpdate::~NarcPrintUpdate()
{
}

basar::Int16 NarcPrintUpdate::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & NarcPrintUpdate::getCreationDateTime() const
{
    return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 NarcPrintUpdate::getRecordType() const
{
    return TransactionRecordBase::getRecordType();
}

basar::Int32 NarcPrintUpdate::getRecordNo() const
{
    return TransactionRecordBase::getRecordNo();
}

const basar::VarString NarcPrintUpdate::getProgramName() const
{
    return getString( 3, 6 ); //size 6
}

basar::Int32 NarcPrintUpdate::getOrderNo() const
{
    return getInt32( 9, 7 ); //size 7
}

basar::Int32 NarcPrintUpdate::getPharmosOrderNo() const
{
    return getInt32( 16, 7 ); //size 7
}

basar::Int32 NarcPrintUpdate::getCustomerNo() const
{
    return getInt32( 23, 7 ); //size 7
}

basar::Int32 NarcPrintUpdate::getWarehouseOrderNo() const
{
	return getInt32( 30, 5 ); //size 5
}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

