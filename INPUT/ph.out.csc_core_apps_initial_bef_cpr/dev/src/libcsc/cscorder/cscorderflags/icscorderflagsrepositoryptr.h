#ifndef GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERFLAGSREPOSITORYPTR_H
#define GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERFLAGSREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace cscorder {
namespace repo {

class ICSCOrderFlagsRepository;
typedef boost::shared_ptr<ICSCOrderFlagsRepository> ICSCOrderFlagsRepositoryPtr;

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERFLAGSREPOSITORYPTR_H
