/*
 * istringresource.h
 *
 *  Created on: 22.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_UTIL_ISTRINGRESOURCE_H
#define GUARD_LIBCSC_UTIL_ISTRINGRESOURCE_H

#include <libbasar_definitions.h>
#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace util {

class IStringResource
{
public:
    virtual ~IStringResource() {}

    virtual basar::VarString getString(basar::VarString const& key) = 0;
};

typedef boost::shared_ptr<IStringResource> IStringResourcePtr;

} // end namespace util
} // end namespace libcsc

#endif // GUARD_LIBCSC_UTIL_ISTRINGRESOURCE_H
