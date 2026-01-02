#ifndef GUARD_LIBCSC_CSCORDER_REPO_ICSCCALLPLANREPOSITORYPTR_H
#define GUARD_LIBCSC_CSCORDER_REPO_ICSCCALLPLANREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace cscorder {
namespace repo {

class ICSCCallplanRepository;
typedef boost::shared_ptr<ICSCCallplanRepository> ICSCCallplanRepositoryPtr;

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_ICSCCALLPLANREPOSITORYPTR_H
