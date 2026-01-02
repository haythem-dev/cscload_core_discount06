#ifndef GUARD_CSC_PHADEX_USECASE_I_BLOCKEDARTICLE_UC_H
#define GUARD_CSC_PHADEX_USECASE_I_BLOCKEDARTICLE_UC_H

#include <libutil/irunnable.h>
#include <domainmodule/phadextransaction/transactionrecord/blockedarticlerecord/iblockedarticlerecordptr.h>

namespace csc_phadex
{
namespace useCase
{
class IBlockedArticleUC : public libutil::useCase::IRunnable
{
public:
	virtual ~IBlockedArticleUC() {}
	virtual void setBlockedArticleRecord(csc_phadex::domMod::phadexTransaction::IBlockedArticleRecordPtr) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_I_BLOCKEDARTICLE_UC_H
