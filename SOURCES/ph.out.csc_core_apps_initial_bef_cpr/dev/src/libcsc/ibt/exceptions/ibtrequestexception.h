/*
 * ibtrequestexception.h
 *
 *  Created on: 15.10.2015
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_IBTREQUESTEXCEPTION_H
#define GUARD_LIBCSC_IBTREQUESTEXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace exceptions {

class IbtRequestException : public CSCExceptionBase
{
public:
    IbtRequestException(basar::ExceptInfo const& sInfo);
    virtual ~IbtRequestException();

private:
    IbtRequestException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBTREQUESTEXCEPTION_H
