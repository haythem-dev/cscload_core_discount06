/*
 * componentmanagerptr.h
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_PROCUREMENTPERMISSION_COMPONENTMANAGER_PTR_H
#define GUARD_LIBCSC_PROCUREMENTPERMISSION_COMPONENTMANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace procurementpermission {

class ComponentManager;
typedef boost::shared_ptr<libcsc::procurementpermission::ComponentManager> ComponentManagerPtr;

} // end namespace ibt
} // end namespace procurementpermission

#endif // GUARD_LIBCSC_PROCUREMENTPERMISSION_COMPONENTMANAGER_PTR_H
