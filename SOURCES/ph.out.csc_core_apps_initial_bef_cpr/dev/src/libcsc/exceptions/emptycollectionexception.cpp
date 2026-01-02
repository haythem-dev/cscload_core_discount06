#include "emptycollectionexception.h"

namespace libcsc
{
namespace exceptions
{
EmptyCollectionException::EmptyCollectionException( const basar::ExceptInfo & sInfo )
: CSCExceptionBase( sInfo, "EmptyCollectionException" )
{
}

EmptyCollectionException::~EmptyCollectionException()
{
}

} // end namespace exceptions
} // end namespace libcsc
