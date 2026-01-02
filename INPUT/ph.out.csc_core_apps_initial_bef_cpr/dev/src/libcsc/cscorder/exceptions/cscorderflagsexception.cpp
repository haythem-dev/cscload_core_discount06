#include "cscorderflagsexception.h"

namespace libcsc {
namespace exceptions {

CSCOrderFlagsException::CSCOrderFlagsException(basar::ExceptInfo const& sInfo)
    : CSCExceptionBase(sInfo, "CSCOrderFlagsException")
{
}

CSCOrderFlagsException::~CSCOrderFlagsException()
{
}

} // end namespace exceptions
} // end namespace libcsc
