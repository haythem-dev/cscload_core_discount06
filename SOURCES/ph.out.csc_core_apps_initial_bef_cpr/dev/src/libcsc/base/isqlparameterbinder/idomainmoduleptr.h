/*
 * idomainmoduleptr.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_BASE_IDOMAINMODULEPTR_H
#define GUARD_LIBCSC_BASE_IDOMAINMODULEPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace base {

class IDomainModule;
typedef boost::shared_ptr<libcsc::base::IDomainModule> IDomainModulePtr;

} // end namespace base
} // end namespace libcsc

#endif // GUARD_LIBCSC_BASE_IDOMAINMODULEPTR_H
