#ifndef GUARD_LIBCSC_I_REBATE_IN_KIND_REPOSITORY_PTR_H
#define GUARD_LIBCSC_I_REBATE_IN_KIND_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IRebateInKindRepository;
typedef boost::shared_ptr<libcsc::discount::IRebateInKindRepository> IRebateInKindRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_REBATE_IN_KIND_REPOSITORY_PTR_H
