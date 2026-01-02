/*
 * repositoryptr.h
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_PROCUREMENTPERMISSION_REPOSITORY_PTR_H
#define GUARD_LIBCSC_PROCUREMENTPERMISSION_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace procurementpermission {
namespace repo {

class Repository;
typedef boost::shared_ptr<Repository> RepositoryPtr;

} // end namespace repo
} // end namespace procurementpermission
} // end namespace libcsc

#endif // GUARD_LIBCSC_PROCUREMENTPERMISSION_REPOSITORY_PTR_H
