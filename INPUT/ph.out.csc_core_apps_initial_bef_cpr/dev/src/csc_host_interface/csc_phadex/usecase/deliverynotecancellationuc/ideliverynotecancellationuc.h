#ifndef GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECANCELLATION_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECANCELLATION_UC_H

#include <libutil/irunnable.h>
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecancellation/ideliverynotecancellationptr.h>

namespace csc_phadex
{
namespace useCase
{
class IDeliveryNoteCancellationUC : public libutil::useCase::IRunnable
{
public:
    virtual ~IDeliveryNoteCancellationUC() {}
    virtual void setDeliveryNoteCancellationRecord(csc_phadex::domMod::phadexTransaction::IDeliveryNoteCancellationPtr) = 0;
//    virtual void injectTenderProgressDM( libtender::domMod::tender::ITenderProgressPtr tenProg ) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECANCELLATION_UC_H
