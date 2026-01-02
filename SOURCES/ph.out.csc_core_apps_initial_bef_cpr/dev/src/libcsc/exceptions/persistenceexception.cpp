#include "persistenceexception.h"

namespace libcsc
{
namespace exceptions
{
PersistenceException::PersistenceException( const basar::ExceptInfo & sInfo, const basar::VarString& exceptionType )
: CSCExceptionBase( sInfo, exceptionType )
{
}

PersistenceException::~PersistenceException()
{
}

} // end namespace exceptions
} // end namespace libcsc
