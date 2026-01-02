#ifndef GUARD_LIBCSC_INVALID_DATA_EXCEPTION_H
#define GUARD_LIBCSC_INVALID_DATA_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc
{
namespace exceptions
{
class InvalidDataException : public CSCExceptionBase
{
public:
	InvalidDataException( const basar::ExceptInfo & sInfo );
	virtual ~InvalidDataException();

private:
	InvalidDataException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_INVALID_DATA_EXCEPTION_H
