#ifndef GUARD_CSC_PHADEX_DOMMOD_SAP_REFERENCE_NO_RECORD_H
#define GUARD_CSC_PHADEX_DOMMOD_SAP_REFERENCE_NO_RECORD_H

#include "isapreferencenorecord.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class SAPReferenceNoRecord : public TransactionRecordBase, public ISAPReferenceNoRecord
                        
{
public:
	SAPReferenceNoRecord( IPhadexTransactionPtr phadexTransaction );
    virtual ~SAPReferenceNoRecord();
    
	virtual basar::Int16 getBranchno() const;
	virtual const basar::DateTime & getCreationDateTime() const;
	virtual basar::Int16 getRecordType() const;
	virtual basar::Int32 getRecordNo() const;

	virtual const basar::VarString getProgramName() const;
	virtual basar::Int32 getCscOrderNo() const;
	virtual basar::Int32 getPharmosOrderNo() const;
	virtual basar::VarString getSapReferenceNo() const;

};

}// end namespace phadexTransaction
}// end namespace domMod
}// end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_SAP_REFERENCE_NO_RECORD_H
