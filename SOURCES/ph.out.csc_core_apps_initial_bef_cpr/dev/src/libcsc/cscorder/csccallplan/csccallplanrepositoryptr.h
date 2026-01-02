#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLAN_REPOSITORYPTR_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLAN_REPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCCallplanRepository;
typedef boost::shared_ptr<CSCCallplanRepository> CSCCallplanRepositoryPtr;

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLAN_REPOSITORYPTR_H
