/*
 * iint32result.h
 *
 *  Created on: 30.06.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_BASE_IINT32RESULT_H
#define GUARD_LIBCSC_BASE_IINT32RESULT_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace base {

class IInt32Result
{
public:
    virtual ~IInt32Result() {}

    virtual basar::Int32 getInt32Result() const = 0;
};

} // end namespace base
} // end namespace libcsc

#endif // GUARD_LIBCSC_BASE_IINT32RESULT_H
