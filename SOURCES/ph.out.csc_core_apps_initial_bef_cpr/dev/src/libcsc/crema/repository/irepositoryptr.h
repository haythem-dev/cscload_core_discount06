/*
 * irepositoryptr.h
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CREMA_IREPOSITORY_PTR_H
#define GUARD_LIBCSC_CREMA_IREPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace crema {
namespace repo {

class IRepository;
typedef boost::shared_ptr<IRepository> IRepositoryPtr;

} // end namespace repo
} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_IREPOSITORY_PTR_H
