#include "namenotfoundexception.h"

namespace libcsc_deli
{
namespace exceptions
{
    NameNotFoundException::NameNotFoundException( const basar::ExceptInfo & sInfo )
    : BaseException( sInfo, "NameNotFoundException" )
    {
    }

    NameNotFoundException::~NameNotFoundException()
    {
    }

} // end namespace exceptions
} // end namespace libcsc_deli
