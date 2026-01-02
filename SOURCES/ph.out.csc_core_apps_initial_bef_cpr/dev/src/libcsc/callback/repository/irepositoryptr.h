/*
 * irepositoryptr.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_IREPOSITORY_PTR_H
#define GUARD_LIBCSC_CALLBACK_IREPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace repo {

class IRepository;
typedef boost::shared_ptr<IRepository> IRepositoryPtr;

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_IREPOSITORY_PTR_H
