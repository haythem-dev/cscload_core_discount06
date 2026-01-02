#ifndef GUARD_CSC_PHADEX_DOMMOD_DELIVERY_NOTE_CANCELLATION_H
#define GUARD_CSC_PHADEX_DOMMOD_DELIVERY_NOTE_CANCELLATION_H

#include "ideliverynotecancellation.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class DeliveryNoteCancellation : public IDeliveryNoteCancellation,
                        public TransactionRecordBase
{
public:
    DeliveryNoteCancellation( IPhadexTransactionPtr phadexTransaction );
    virtual ~DeliveryNoteCancellation();
    
    virtual const basar::VarString getProgramName() const;
    virtual basar::Int32 getCustomerNo() const;
    virtual const basar::VarString getInvoiceNo() const;
    virtual basar::Date getInvoiceDate() const;
    virtual basar::Int16 getStornoFlag() const;       // 1=STORNO-, 0 = ENTSTORNIERT

    virtual basar::Int16 getBranchno() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;
};

}// end namespace phadexTransaction
}// end namespace domMod
}// end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_DELIVERY_NOTE_CANCELLATION_H
