#include "deliverynotecancellation.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
DeliveryNoteCancellation::DeliveryNoteCancellation( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction )
{
}

DeliveryNoteCancellation::~DeliveryNoteCancellation()
{
}

basar::Int16 DeliveryNoteCancellation::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & DeliveryNoteCancellation::getCreationDateTime() const
{
    return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 DeliveryNoteCancellation::getRecordType() const
{
    return TransactionRecordBase::getRecordType();
}

basar::Int32 DeliveryNoteCancellation::getRecordNo() const
{
    return TransactionRecordBase::getRecordNo();
}

const basar::VarString DeliveryNoteCancellation::getProgramName() const
{
    return getString( 3, 6 ); //size 6
}

basar::Int32 DeliveryNoteCancellation::getCustomerNo() const
{
    return getInt32( 9, 7 ); //size 7
}

const basar::VarString DeliveryNoteCancellation::getInvoiceNo() const
{
    return getString( 16, 10 ); //size 10
}

basar::Date DeliveryNoteCancellation::getInvoiceDate() const
{
    return getDate(26, 8); //size 8
}

basar::Int16 DeliveryNoteCancellation::getStornoFlag() const
{
    return getInt16( 34, 1 ); //size 1
}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

