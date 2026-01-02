#ifndef GUARD_CSC_PHADEX_DOMMOD_I_SAP_REFERENCE_NO_RECORD_H
#define GUARD_CSC_PHADEX_DOMMOD_I_SAP_REFERENCE_NO_RECORD_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class ISAPReferenceNoRecord : public ITransactionRecord
{
public:
    virtual ~ISAPReferenceNoRecord() {}

	virtual const basar::VarString getProgramName() const = 0;
	virtual basar::Int32 getCscOrderNo() const = 0;
	virtual basar::Int32 getPharmosOrderNo() const = 0;
	virtual basar::VarString getSapReferenceNo() const = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_SAP_REFERENCE_NO_RECORD_H
