#include "filenotfoundexception.h"

namespace libcsc_deli
{
namespace exceptions
{
    FileNotFoundException::FileNotFoundException( const basar::ExceptInfo & sInfo )
    : BaseException( sInfo, "FileNotFoundException" )
    {
    }

    FileNotFoundException::~FileNotFoundException()
    {
    }

} // end namespace exceptions
} // end namespace libcsc_deli
