#ifndef GUARD_CSC_PHADEX_USECASE_I_TRANSFER_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_TRANSFER_UC_H

#include <libutil/irunnable.h>

namespace csc_phadex
{
namespace useCase
{
class ITransferUC : public libutil::useCase::IRunnable
{
public:
	virtual ~ITransferUC() {}
	virtual bool hasRecordsLeft() const = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_TRANSFER_UC_H
