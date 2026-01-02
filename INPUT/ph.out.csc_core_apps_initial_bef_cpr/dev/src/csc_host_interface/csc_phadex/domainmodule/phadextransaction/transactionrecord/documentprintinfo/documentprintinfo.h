#ifndef GUARD_CSC_PHADEX_DOMMOD_DOCUMENT_PRINT_INFO_H
#define GUARD_CSC_PHADEX_DOMMOD_DOCUMENT_PRINT_INFO_H

#include "idocumentprintinfo.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class DocumentPrintInfo : public IDocumentPrintInfo,
                          public TransactionRecordBase
{
public:
	DocumentPrintInfo( IPhadexTransactionPtr phadexTransaction );
    virtual ~DocumentPrintInfo();

	virtual basar::Int32 getCustomerNo() const;
	virtual basar::Int32 getDocumentDate() const;
    virtual const basar::VarString getDocumentNo() const;
    virtual basar::Int32 getDocumentType() const;

	virtual basar::Int16 getBranchno() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;
};

}// end namespace phadexTransaction
}// end namespace domMod
}// end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_DOCUMENT_PRINT_INFO_H
