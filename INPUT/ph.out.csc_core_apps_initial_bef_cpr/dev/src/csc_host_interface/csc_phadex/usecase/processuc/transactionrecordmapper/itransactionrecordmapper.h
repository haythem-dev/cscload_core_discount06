#ifndef GUARD_CSC_PHADEX_USECASE_I_TRANSACTION_RECORD_MAPPER_H
#define GUARD_CSC_PHADEX_USECASE_I_TRANSACTION_RECORD_MAPPER_H

#include <libutil/irunnableptr.h>
#include <domainmodule/phadextransaction/iphadextransactionptr.h>


namespace csc_phadex
{
namespace useCase
{
class ITransactionRecordMapper
{
public:
	virtual ~ITransactionRecordMapper() {}
    virtual libutil::useCase::IRunnablePtr map( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr ) = 0;
};

} // namespace useCase
} // namespace csc_phadex

#endif // GUARD_CSC_PHADEX_USECASE_I_TRANSACTION_RECORD_MAPPER_H
