#ifndef GUARD_CSC_PHADEX_USECASE_I_DOCUMENTPRINTINFO_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_DOCUMENTPRINTINFO_UC_H

#include <libutil/irunnable.h>
#include "domainmodule/phadextransaction/transactionrecord/documentprintinfo/idocumentprintinfoptr.h"

namespace csc_phadex
{
namespace useCase
{
class IDocumentPrintInfoUC : public libutil::useCase::IRunnable
{
public:
    virtual ~IDocumentPrintInfoUC() {}
    virtual void setDocumentPrintInfo(csc_phadex::domMod::phadexTransaction::IDocumentPrintInfoPtr) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_DOCUMENTPRINTINFO_UC_H
