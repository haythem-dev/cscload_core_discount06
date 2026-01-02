#ifndef GUARD_CSC_PHADEX_DOMMOD_TENDER_INVOICE_CANCELLATION_RECORD_H
#define GUARD_CSC_PHADEX_DOMMOD_TENDER_INVOICE_CANCELLATION_RECORD_H

#include "itenderinvoicecancellationrecord.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>
#include <domainmodule/phadextransaction/transactionrecord/itransactionrecordptr.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class TenderInvoiceCancellationRecord : public ITenderInvoiceCancellationRecord,
										public TransactionRecordBase
{
public:
	TenderInvoiceCancellationRecord( IPhadexTransactionPtr phadexTransaction ); 
	virtual ~TenderInvoiceCancellationRecord();

	virtual const basar::VarString getProgramName() const;
    virtual basar::Int32 getInvoiceNo() const;
    virtual basar::Int32 getInvoiceDate() const;
    virtual basar::Int32 getCustomerNo() const;
    virtual basar::Int32 getArticleNo() const;
    virtual basar::Int32 getInvoiceQty() const;
    virtual basar::Int32 getOrderNo() const;

    virtual basar::Int16 getBranchno() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;




};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_TENDER_INVOICE_CANCELLATION_RECORD_H
