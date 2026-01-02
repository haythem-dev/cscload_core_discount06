#ifndef GUARD_CSC_PHADEX_USECASE_TRANSACTION_RECORD_MAPPER_PTR_H
#define GUARD_CSC_PHADEX_USECASE_TRANSACTION_RECORD_MAPPER_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace useCase
{
	class TransactionRecordMapper;
	typedef boost::shared_ptr< csc_phadex::useCase::TransactionRecordMapper > TransactionRecordMapperPtr;

} // namespace useCase
} // namespace csc_phadex

#endif // GUARD_CSC_PHADEX_USECASE_TRANSACTION_RECORD_MAPPER_PTR_H
