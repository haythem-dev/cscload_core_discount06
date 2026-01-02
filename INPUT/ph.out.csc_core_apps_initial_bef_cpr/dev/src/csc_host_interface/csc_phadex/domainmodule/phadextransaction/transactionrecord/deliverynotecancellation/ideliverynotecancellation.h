#ifndef GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_CANCELLATION_H
#define GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_CANCELLATION_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class IDeliveryNoteCancellation : public ITransactionRecord
{
public:
    virtual ~IDeliveryNoteCancellation() {}

    virtual const basar::VarString getProgramName() const = 0;
    virtual basar::Int32 getCustomerNo() const = 0;
    virtual const basar::VarString getInvoiceNo() const = 0;
    virtual basar::Date getInvoiceDate() const = 0;
    virtual basar::Int16 getStornoFlag() const = 0;      // 1=STORNO-, 0 = ENTSTORNIERT
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_CANCELLATION_H
