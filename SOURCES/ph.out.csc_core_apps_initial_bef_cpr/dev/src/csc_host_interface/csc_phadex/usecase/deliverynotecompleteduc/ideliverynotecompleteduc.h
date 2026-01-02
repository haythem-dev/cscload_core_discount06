#ifndef GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECOMPLETED_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECOMPLETED_UC_H

#include <libutil/irunnable.h>
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecompleted/ideliverynotecompletedptr.h>

namespace csc_phadex
{
namespace useCase
{
class IDeliveryNoteCompletedUC : public libutil::useCase::IRunnable
{
public:
	virtual ~IDeliveryNoteCompletedUC() {}
	virtual void setDeliveryNoteCompletedRecord(csc_phadex::domMod::phadexTransaction::IDeliveryNoteCompletedPtr) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECOMPLETED_UC_H
