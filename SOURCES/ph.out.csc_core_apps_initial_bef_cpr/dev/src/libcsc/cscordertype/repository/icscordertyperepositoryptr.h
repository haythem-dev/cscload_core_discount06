#ifndef GUARD_LIBCSC_I_CSCORDERTYPE_REPOSITORY_PTR_H
#define GUARD_LIBCSC_I_CSCORDERTYPE_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace cscordertype
{
class ICSCOrderTypeRepository;
typedef boost::shared_ptr<libcsc::cscordertype::ICSCOrderTypeRepository> ICSCOrderTypeRepositoryPtr;

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_CSCORDERTYPE_REPOSITORY_PTR_H
