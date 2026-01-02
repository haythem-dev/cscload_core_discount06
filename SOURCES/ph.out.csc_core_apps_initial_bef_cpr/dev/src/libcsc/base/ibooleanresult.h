/*
 * ibooleanresult.h
 *
 *  Created on: 07.09.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_BASE_IBOOLEANRESULT_H
#define GUARD_LIBCSC_BASE_IBOOLEANRESULT_H

namespace libcsc {
namespace base {

class IBooleanResult
{
public:
    virtual ~IBooleanResult() {}

    virtual bool getBooleanResult() const = 0;
};

} // end namespace base
} // end namespace libcsc

#endif // GUARD_LIBCSC_BASE_IBOOLEANRESULT_H
