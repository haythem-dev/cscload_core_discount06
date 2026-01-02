#ifndef GUARD_CSC_PHADEX_USECASE_I_NARCPRINTUPDATE_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_NARCPRINTUPDATE_UC_H

#include <libutil/irunnable.h>
#include "domainmodule/phadextransaction/transactionrecord/narcprintupdate/inarcprintupdateptr.h"

namespace csc_phadex
{
namespace useCase
{
class INarcPrintUpdateUC : public libutil::useCase::IRunnable
{
public:
    virtual ~INarcPrintUpdateUC() {}
    virtual void setNarcPrintUpdate( csc_phadex::domMod::phadexTransaction::INarcPrintUpdatePtr ) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_NARCPRINTUPDATE_UC_H
