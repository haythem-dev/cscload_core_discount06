#ifndef GUARD_LIBCSC_SQLDUPLICATE_EXCEPTION_H
#define GUARD_LIBCSC_SQLDUPLICATE_EXCEPTION_H

#include <exceptions/persistenceexception.h>

namespace libcsc {
namespace exceptions {

class SqlDuplicateException : public PersistenceException
{
public:
    SqlDuplicateException(basar::ExceptInfo const& sInfo);
    virtual ~SqlDuplicateException();

private:
	SqlDuplicateException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_SQLDUPLICATE_EXCEPTION_H
