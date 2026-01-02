#include "deliverynotecompleted.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
DeliveryNoteCompleted::DeliveryNoteCompleted( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction )
{
}

DeliveryNoteCompleted::~DeliveryNoteCompleted()
{
}

basar::Int16 DeliveryNoteCompleted::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & DeliveryNoteCompleted::getCreationDateTime() const
{
    return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 DeliveryNoteCompleted::getRecordType() const
{
    return TransactionRecordBase::getRecordType();
}

basar::Int32 DeliveryNoteCompleted::getRecordNo() const
{
    return TransactionRecordBase::getRecordNo();
}

const basar::VarString DeliveryNoteCompleted::getProgramName() const
{
    return getString( 3, 6 ); //size 6
}

basar::Int32 DeliveryNoteCompleted::getCustomerNo() const
{
    return getInt32( 9, 7 ); //size 7
}

basar::Int32 DeliveryNoteCompleted::getCscOrderNo() const
{
    return getInt32( 16, 7 ); //size 7
}

const basar::VarString DeliveryNoteCompleted::getInvoiceNo() const
{
    return getString( 23, 10 ); //size 10
}

basar::Int16 DeliveryNoteCompleted::getMode() const
{
    return getInt16( 33, 1 ); //size 1
}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

