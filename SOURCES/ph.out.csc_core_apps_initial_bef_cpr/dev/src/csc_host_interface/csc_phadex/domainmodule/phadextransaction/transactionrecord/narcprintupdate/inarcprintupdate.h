#ifndef GUARD_CSC_PHADEX_DOMMOD_I_NARC_PRINT_UPDATE_H
#define GUARD_CSC_PHADEX_DOMMOD_I_NARC_PRINT_UPDATE_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class INarcPrintUpdate : public ITransactionRecord
{
public:
    virtual ~INarcPrintUpdate() {}

    virtual const basar::VarString getProgramName() const = 0;
    virtual basar::Int32 getOrderNo() const = 0;
    virtual basar::Int32 getPharmosOrderNo() const = 0;
    virtual basar::Int32 getCustomerNo() const = 0;
	virtual basar::Int32 getWarehouseOrderNo() const = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_NARC_PRINT_UPDATE_H
