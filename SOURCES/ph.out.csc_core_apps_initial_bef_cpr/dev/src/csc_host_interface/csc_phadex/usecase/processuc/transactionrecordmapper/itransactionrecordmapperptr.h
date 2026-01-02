#ifndef GUARD_CSC_PHADEX_USECASE_I_TRANSACTION_RECORD_MAPPER_PTR_H
#define GUARD_CSC_PHADEX_USECASE_I_TRANSACTION_RECORD_MAPPER_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace useCase
{
	class ITransactionRecordMapper;
	typedef boost::shared_ptr< csc_phadex::useCase::ITransactionRecordMapper > ITransactionRecordMapperPtr;

} // namespace useCase
} // namespace csc_phadex

#endif // GUARD_CSC_PHADEX_USECASE_I_TRANSACTION_RECORD_MAPPER_PTR_H
