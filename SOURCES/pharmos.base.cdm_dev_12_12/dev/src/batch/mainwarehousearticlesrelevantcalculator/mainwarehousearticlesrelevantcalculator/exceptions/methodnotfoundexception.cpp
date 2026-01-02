#include "methodnotfoundexception.h"

namespace mainwarehousearticlesrelevantcalculator
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
} // end namespace mainwarehousearticlesrelevantcalculator
