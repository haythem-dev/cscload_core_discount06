#ifndef GUARD_LIBCSC_CSC_EXCEPTION_BASE_H
#define GUARD_LIBCSC_CSC_EXCEPTION_BASE_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_exceptions.h>

namespace libcsc
{
namespace exceptions
{
class CSCExceptionBase : public basar::Exception
{
public:
	CSCExceptionBase( const basar::ExceptInfo & sInfo, const basar::VarString & exceptionType );
	virtual ~CSCExceptionBase();

	const basar::VarString & reason() const;

private:
	CSCExceptionBase();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSC_EXCEPTION_BASE_H
