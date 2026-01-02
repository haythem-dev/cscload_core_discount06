#include "methodnotfoundexception.h"

namespace libcsc_deli
{
namespace exceptions
{
    MethodNotFoundException::MethodNotFoundException( const basar::ExceptInfo & sInfo )
    : BaseException( sInfo, "MethodNotFoundException" )
    {
    }

    MethodNotFoundException::~MethodNotFoundException()
    {
    }

} // end namespace exceptions
} // end namespace libcsc_deli
