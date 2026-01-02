#include "norulefoundexception.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    NoRuleFoundException::NoRuleFoundException( const basar::ExceptInfo& sInfo )
        : BaseException( sInfo, "NoRuleFoundException" )
    {
    }
    NoRuleFoundException::~NoRuleFoundException()
    {
    }

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator
