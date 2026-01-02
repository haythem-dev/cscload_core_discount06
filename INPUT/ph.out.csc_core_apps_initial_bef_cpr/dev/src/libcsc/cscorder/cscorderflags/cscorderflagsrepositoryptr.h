#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGS_REPOSITORYPTR_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGS_REPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderFlagsRepository;
typedef boost::shared_ptr<CSCOrderFlagsRepository> CSCOrderFlagsRepositoryPtr;

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGS_REPOSITORYPTR_H
