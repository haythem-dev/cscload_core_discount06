#ifndef GUARD_LIBCSC_PERSISTENCE_EXCEPTION_H
#define GUARD_LIBCSC_PERSISTENCE_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc
{
namespace exceptions
{
class PersistenceException : public CSCExceptionBase
{
public:
	PersistenceException( const basar::ExceptInfo & sInfo, const basar::VarString& exceptionType = basar::VarString("PersistenceException") );
	virtual ~PersistenceException();

private:
	PersistenceException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_EXCEPTION_H
