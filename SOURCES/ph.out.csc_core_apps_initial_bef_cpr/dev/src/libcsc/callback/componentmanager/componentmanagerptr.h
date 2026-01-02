/*
 * componentmanagerptr.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_COMPONENTMANAGER_PTR_H
#define GUARD_LIBCSC_CALLBACK_COMPONENTMANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {

class ComponentManager;
typedef boost::shared_ptr<libcsc::callback::ComponentManager> ComponentManagerPtr;

} // end namespace ibt
} // end namespace callback

#endif // GUARD_LIBCSC_CALLBACK_COMPONENTMANAGER_PTR_H
