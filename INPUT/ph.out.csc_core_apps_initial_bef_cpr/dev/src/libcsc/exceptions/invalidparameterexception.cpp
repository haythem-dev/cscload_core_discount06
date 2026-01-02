#include "invalidparameterexception.h"

namespace libcsc
{
namespace exceptions
{
InvalidParameterException::InvalidParameterException( const basar::ExceptInfo & sInfo )
: CSCExceptionBase( sInfo, "InvalidParameterException" )
{
}

InvalidParameterException::~InvalidParameterException()
{
}

} // end namespace exceptions
} // end namespace libcsc
