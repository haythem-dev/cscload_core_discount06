/*
 * repositoryptr.h
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPOSITORY_PTR_H
#define GUARD_LIBCSC_CALLBACK_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace crema {
namespace repo {

class Repository;
typedef boost::shared_ptr<Repository> RepositoryPtr;

} // end namespace repo
} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPOSITORY_PTR_H
