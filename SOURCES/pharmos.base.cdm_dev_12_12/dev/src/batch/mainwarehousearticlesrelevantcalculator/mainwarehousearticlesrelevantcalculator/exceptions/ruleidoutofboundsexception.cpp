#include "ruleidoutofboundsexception.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    RuleIDOutOfBoundsException::RuleIDOutOfBoundsException( const basar::ExceptInfo& sInfo )
        : BaseException( sInfo, "RuleIDOutOfBoundsException" )
    {
    }
    RuleIDOutOfBoundsException::~RuleIDOutOfBoundsException()
    {
    }

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator
