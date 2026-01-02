#include "duplicatenameexception.h"

namespace libcsc_deli
{
namespace exceptions
{
    DuplicateNameException::DuplicateNameException( const basar::ExceptInfo & sInfo )
    : BaseException( sInfo, "DuplicateNameException" )
    {
    }

    DuplicateNameException::~DuplicateNameException()
    {
    }

} // end namespace exceptions
} // end namespace libcsc_deli
