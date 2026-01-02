#include "datanotfoundexception.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    DataNotFoundException::DataNotFoundException( const basar::ExceptInfo& sInfo )
        : BaseException( sInfo, "DataNotFoundException" )
    {
    }
    DataNotFoundException::~DataNotFoundException()
    {
    }

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator
