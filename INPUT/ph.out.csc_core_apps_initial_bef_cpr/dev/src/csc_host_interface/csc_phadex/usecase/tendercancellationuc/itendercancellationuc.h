#ifndef GUARD_CSC_PHADEX_USECASE_I_TENCERCANCELLATION_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_TENCERCANCELLATION_UC_H

#include <libutil/irunnable.h>
#include <domainmodule/phadextransaction/transactionrecord/tenderinvoicecancellation/itenderinvoicecancellationrecordptr.h>

namespace csc_phadex
{
namespace useCase
{
class ITenderCancellationUC : public libutil::useCase::IRunnable
{
public:
	virtual ~ITenderCancellationUC() {}
    virtual void setTenderInvoiceCancellationRecord(csc_phadex::domMod::phadexTransaction::ITenderInvoiceCancellationRecordPtr) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_TENCERCANCELLATION_UC_H
