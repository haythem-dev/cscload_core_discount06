#include "documentprintinfo.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{

DocumentPrintInfo::DocumentPrintInfo( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction )
{
}

DocumentPrintInfo::~DocumentPrintInfo()
{
}

basar::Int16 DocumentPrintInfo::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & DocumentPrintInfo::getCreationDateTime() const
{
    return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 DocumentPrintInfo::getRecordType() const
{
    return TransactionRecordBase::getRecordType();
}

basar::Int32 DocumentPrintInfo::getRecordNo() const
{
    return TransactionRecordBase::getRecordNo();
}

basar::Int32 DocumentPrintInfo::getCustomerNo() const
{
    return getInt32(3, 7); //size 7
}

basar::Int32 DocumentPrintInfo::getDocumentDate() const
{
    return getInt32( 10, 8 ); //size 8
}

const basar::VarString DocumentPrintInfo::getDocumentNo() const
{
    return getString( 18, 10 ); //size 7
}

basar::Int32 DocumentPrintInfo::getDocumentType() const
{
    return getInt32( 28, 3 ); //size 7
}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex
