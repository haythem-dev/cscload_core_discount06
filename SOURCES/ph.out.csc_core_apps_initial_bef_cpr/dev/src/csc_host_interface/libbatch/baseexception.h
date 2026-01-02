#ifndef GUARD_UTIL_BASE_EXCEPTION_H
#define GUARD_UTIL_BASE_EXCEPTION_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_exceptions.h>

namespace util
{
class BaseException : public basar::Exception
{
public:
	BaseException( const basar::ExceptInfo & sInfo, const basar::VarString & exceptionType );
	virtual ~BaseException();

	const basar::VarString & reason() const;

private:
	BaseException();
};

} // end namespace util

#endif // GUARD_UTIL_BASE_EXCEPTION_H
