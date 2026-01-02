#ifndef GUARD_CSC_PHADEX_DOMMOD_DELIVERY_NOTE_COMPLETED_H
#define GUARD_CSC_PHADEX_DOMMOD_DELIVERY_NOTE_COMPLETED_H

#include "ideliverynotecompleted.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class DeliveryNoteCompleted : public IDeliveryNoteCompleted,
                        public TransactionRecordBase
{
public:
    DeliveryNoteCompleted( IPhadexTransactionPtr phadexTransaction );
    virtual ~DeliveryNoteCompleted();
    
    virtual const basar::VarString getProgramName() const;
    virtual basar::Int32 getCustomerNo() const;
    virtual basar::Int32 getCscOrderNo() const;
    virtual const basar::VarString getInvoiceNo() const;
    virtual basar::Int16 getMode() const;		// 0=KUNDEN-, 1=SHUTTLE-AUFTRAG

    virtual basar::Int16 getBranchno() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;
};

}// end namespace phadexTransaction
}// end namespace domMod
}// end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_DELIVERY_NOTE_COMPLETED_H
