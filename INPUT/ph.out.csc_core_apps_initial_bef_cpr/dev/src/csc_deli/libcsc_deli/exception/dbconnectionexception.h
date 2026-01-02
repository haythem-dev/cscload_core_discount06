#ifndef GUARD_LIBCSC_DELI_EXCEPTIONS_DBCONNECTIONEXCEPTION_H
#define GUARD_LIBCSC_DELI_EXCEPTIONS_DBCONNECTIONEXCEPTION_H

#include <libutil/exception.h>

namespace libcsc_deli
{
namespace exceptions
{
    class DBConnectionException : public libutil::exceptions::BaseException
    {
    public:
        DBConnectionException( const basar::ExceptInfo & sInfo );
        ~DBConnectionException();

    private:
        DBConnectionException();
    };

} // end namespace exceptions
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_EXCEPTIONS_DBCONNECTIONEXCEPTION_H
