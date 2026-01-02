#ifndef GUARD_LIBCSC_INVALID_PARAMETER_EXCEPTION_H
#define GUARD_LIBCSC_INVALID_PARAMETER_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc
{
namespace exceptions
{
class InvalidParameterException : public CSCExceptionBase
{
public:
	InvalidParameterException( const basar::ExceptInfo & sInfo );
	virtual ~InvalidParameterException();

private:
	InvalidParameterException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_INVALID_PARAMETER_EXCEPTION_H
