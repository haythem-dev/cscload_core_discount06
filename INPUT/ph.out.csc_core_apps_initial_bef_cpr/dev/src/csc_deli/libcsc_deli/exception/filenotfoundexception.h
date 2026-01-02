#ifndef GUARD_LIBCSC_DELI_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H
#define GUARD_LIBCSC_DELI_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H

#include <libutil/exception.h>

namespace libcsc_deli
{
namespace exceptions
{
    class FileNotFoundException : public libutil::exceptions::BaseException
    {
    public:
        FileNotFoundException( const basar::ExceptInfo & sInfo );
        ~FileNotFoundException();

    private:
        FileNotFoundException();
    };

} // end namespace exceptions
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H
