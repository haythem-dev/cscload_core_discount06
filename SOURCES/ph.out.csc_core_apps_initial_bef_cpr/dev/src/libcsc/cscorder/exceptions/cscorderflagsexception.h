#ifndef GUARD_LIBCSC_CSCORDERFLAGSEXCEPTION_H
#define GUARD_LIBCSC_CSCORDERFLAGSEXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace exceptions {

class CSCOrderFlagsException : public CSCExceptionBase
{
public:
    CSCOrderFlagsException(basar::ExceptInfo const& sInfo);
    virtual ~CSCOrderFlagsException();

private:
    CSCOrderFlagsException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERFLAGSEXCEPTION_H
