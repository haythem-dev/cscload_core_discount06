#ifndef GUARD_CSC_PHADEX_USECASE_I_SAPREFERENCENO_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_SAPREFERENCENO_UC_H

#include <libutil/irunnable.h>
#include "domainmodule/phadextransaction/transactionrecord/sapreferencenorecord/isapreferencenorecordptr.h"

namespace csc_phadex
{
namespace useCase
{
class ISAPReferenceNoUC : public libutil::useCase::IRunnable
{
public:
    virtual ~ISAPReferenceNoUC() {}
    virtual void setSAPReferenceNoRecord(csc_phadex::domMod::phadexTransaction::ISAPReferenceNoRecordPtr) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_SAPREFERENCENO_UC_H
