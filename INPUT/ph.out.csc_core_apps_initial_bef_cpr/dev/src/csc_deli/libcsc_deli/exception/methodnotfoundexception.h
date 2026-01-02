#ifndef GUARD_LIBCSC_DELI_EXCEPTIONS_METHODNOTFOUNDEXCEPTION_H
#define GUARD_LIBCSC_DELI_EXCEPTIONS_METHODNOTFOUNDEXCEPTION_H

#include <libutil/exception.h>

namespace libcsc_deli
{
namespace exceptions
{
    class MethodNotFoundException : public libutil::exceptions::BaseException
    {
    public:
        MethodNotFoundException( const basar::ExceptInfo & sInfo );
        ~MethodNotFoundException();

    private:
        MethodNotFoundException();
    };

} // end namespace exceptions
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_EXCEPTIONS_METHODNOTFOUNDEXCEPTION_H
