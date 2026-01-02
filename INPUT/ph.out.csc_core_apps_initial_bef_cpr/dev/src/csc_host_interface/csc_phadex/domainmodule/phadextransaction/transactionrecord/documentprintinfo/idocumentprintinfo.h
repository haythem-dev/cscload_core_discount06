#ifndef GUARD_CSC_PHADEX_DOMMOD_I_DOCUMENT_PRINT_INFO_H
#define GUARD_CSC_PHADEX_DOMMOD_I_DOCUMENT_PRINT_INFO_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class IDocumentPrintInfo : public ITransactionRecord
{
public:
    virtual ~IDocumentPrintInfo() {}

    virtual basar::Int32 getCustomerNo() const = 0;
    virtual basar::Int32 getDocumentDate() const = 0;
    virtual const basar::VarString getDocumentNo() const = 0;
    virtual basar::Int32 getDocumentType() const = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_DOCUMENT_PRINT_INFO_H
