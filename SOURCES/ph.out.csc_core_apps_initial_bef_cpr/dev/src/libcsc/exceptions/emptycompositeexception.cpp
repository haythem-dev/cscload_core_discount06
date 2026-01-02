#include "emptycompositeexception.h"

namespace libcsc
{
namespace exceptions
{
EmptyCompositeException::EmptyCompositeException( const basar::ExceptInfo & sInfo )
: CSCExceptionBase( sInfo, "EmptyCompositeException" )
{
}

EmptyCompositeException::~EmptyCompositeException()
{
}

} // end namespace exceptions
} // end namespace libcsc
