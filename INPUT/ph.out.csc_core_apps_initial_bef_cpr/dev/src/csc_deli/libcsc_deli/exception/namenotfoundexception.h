#ifndef GUARD_LIBCSC_DELI_EXCEPTIONS_NAMENOTFOUNDEXCEPTION_H
#define GUARD_LIBCSC_DELI_EXCEPTIONS_NAMENOTFOUNDEXCEPTION_H

#include <libutil/exception.h>

namespace libcsc_deli
{
namespace exceptions
{
    class NameNotFoundException : public libutil::exceptions::BaseException
    {
    public:
        NameNotFoundException( const basar::ExceptInfo & sInfo );
        ~NameNotFoundException();

    private:
        NameNotFoundException();
    };

} // end namespace exceptions
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_EXCEPTIONS_NAMENOTFOUNDEXCEPTION_H
