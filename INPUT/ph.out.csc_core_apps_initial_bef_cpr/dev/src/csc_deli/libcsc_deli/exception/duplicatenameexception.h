#ifndef GUARD_LIBCSC_DELI_EXCEPTIONS_DUPLICATENAMEEXCEPTION_H
#define GUARD_LIBCSC_DELI_EXCEPTIONS_DUPLICATENAMEEXCEPTION_H

#include <libutil/exception.h>

namespace libcsc_deli
{
namespace exceptions
{
    class DuplicateNameException : public libutil::exceptions::BaseException
    {
    public:
        DuplicateNameException( const basar::ExceptInfo & sInfo );
        ~DuplicateNameException();

    private:
        DuplicateNameException();
    };

} // end namespace exceptions
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_EXCEPTIONS_DUPLICATENAMEEXCEPTION_H
