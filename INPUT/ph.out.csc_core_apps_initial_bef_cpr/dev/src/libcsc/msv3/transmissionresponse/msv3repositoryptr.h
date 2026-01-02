#ifndef GUARD_LIBCSC_MSV3_MSV3REPOSITORY_PTR_H
#define GUARD_LIBCSC_MSV3_MSV3REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace msv3 {
namespace repo {

class MSV3Repository;
typedef boost::shared_ptr<MSV3Repository> MSV3RepositoryPtr;

} // end namespace repo
} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_MSV3REPOSITORY_PTR_H
