
#ifndef GUARD_LIBCSC_MSV3_IMSV3REPOSITORYPTR_H
#define GUARD_LIBCSC_MSV3_IMSV3REPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace msv3 {
namespace repo {

class IMSV3Repository;
typedef boost::shared_ptr<IMSV3Repository> IMSV3RepositoryPtr;

} // end namespace repo
} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_IMSV3REPOSITORYPTR_H
