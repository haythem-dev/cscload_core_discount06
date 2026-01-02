#include "propertyunsetexception.h"

namespace libcsc
{
namespace exceptions
{
PropertyUnsetException::PropertyUnsetException( const basar::ExceptInfo & sInfo )
: CSCExceptionBase( sInfo, "PropertyUnsetException" )
{
}

PropertyUnsetException::~PropertyUnsetException()
{
}

} // end namespace exceptions
} // end namespace libcsc
