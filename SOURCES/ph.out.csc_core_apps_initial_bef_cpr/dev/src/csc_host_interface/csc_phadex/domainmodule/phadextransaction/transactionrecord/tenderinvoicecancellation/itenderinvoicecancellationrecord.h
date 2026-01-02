#ifndef GUARD_CSC_PHADEX_DOMMOD_I_TENDER_INVOICE_CANCELLATION_RECORD_H
#define GUARD_CSC_PHADEX_DOMMOD_I_TENDER_INVOICE_CANCELLATION_RECORD_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>
#include <libbasarcmnutil_bstring.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class ITenderInvoiceCancellationRecord : public ITransactionRecord
{
public:
	virtual ~ITenderInvoiceCancellationRecord() {}

	virtual const basar::VarString getProgramName() const = 0;
    virtual basar::Int32 getInvoiceNo() const = 0;
    virtual basar::Int32 getInvoiceDate() const = 0;
    virtual basar::Int32 getCustomerNo() const = 0;
    virtual basar::Int32 getArticleNo() const = 0;
    virtual basar::Int32 getInvoiceQty() const = 0;
    virtual basar::Int32 getOrderNo() const = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_TENDER_INVOICE_CANCELLATION_RECORD_H
