#ifndef GUARD_CSC_PHADEX_DOMMOD_NARC_PRINT_UPDATE_H
#define GUARD_CSC_PHADEX_DOMMOD_NARC_PRINT_UPDATE_H

#include "inarcprintupdate.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class NarcPrintUpdate : public INarcPrintUpdate,
                        public TransactionRecordBase
{
public:
    NarcPrintUpdate( IPhadexTransactionPtr phadexTransaction );
    virtual ~NarcPrintUpdate();
    
    virtual const basar::VarString getProgramName() const;
    virtual basar::Int32 getOrderNo() const;
    virtual basar::Int32 getPharmosOrderNo() const;
    virtual basar::Int32 getCustomerNo() const;
	virtual basar::Int32 getWarehouseOrderNo() const;

    virtual basar::Int16 getBranchno() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;




};

}// end namespace phadexTransaction
}// end namespace domMod
}// end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_NARC_PRINT_UPDATE_H
