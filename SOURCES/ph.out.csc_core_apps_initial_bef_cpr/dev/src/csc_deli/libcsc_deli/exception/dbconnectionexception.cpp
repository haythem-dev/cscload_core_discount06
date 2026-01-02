#include "dbconnectionexception.h"

namespace libcsc_deli
{
namespace exceptions
{
    DBConnectionException::DBConnectionException( const basar::ExceptInfo & sInfo )
    : BaseException( sInfo, "DBConnectionException" )
    {
    }

    DBConnectionException::~DBConnectionException()
    {
    }

} // end namespace exceptions
} // end namespace libcsc_deli
