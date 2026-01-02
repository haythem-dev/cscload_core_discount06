#include "sqlduplicateexception.h"

namespace libcsc {
namespace exceptions {

SqlDuplicateException::SqlDuplicateException(basar::ExceptInfo const& sInfo) : PersistenceException(sInfo, "SqlDuplicateException")
{
}

SqlDuplicateException::~SqlDuplicateException()
{
}

} // end namespace exceptions
} // end namespace libcsc
