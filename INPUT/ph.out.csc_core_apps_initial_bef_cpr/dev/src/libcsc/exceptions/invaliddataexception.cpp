#include "invaliddataexception.h"

namespace libcsc
{
namespace exceptions
{
InvalidDataException::InvalidDataException( const basar::ExceptInfo & sInfo )
: CSCExceptionBase( sInfo, "InvalidDataException" )
{
}

InvalidDataException::~InvalidDataException()
{
}

} // end namespace exceptions
} // end namespace libcsc
