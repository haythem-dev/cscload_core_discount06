#ifndef GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_COMPLETED_H
#define GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_COMPLETED_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class IDeliveryNoteCompleted : public ITransactionRecord
{
public:
    virtual ~IDeliveryNoteCompleted() {}

    virtual const basar::VarString getProgramName() const = 0;
    virtual basar::Int32 getCustomerNo() const = 0;
    virtual basar::Int32 getCscOrderNo() const = 0;
    virtual const basar::VarString getInvoiceNo() const = 0;
    virtual basar::Int16 getMode() const = 0;		// 0=KUNDEN-, 1=SHUTTLE-AUFTRAG
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_COMPLETED_H
