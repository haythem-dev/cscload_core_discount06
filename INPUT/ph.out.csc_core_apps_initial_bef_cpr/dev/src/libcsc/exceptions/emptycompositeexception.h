#ifndef GUARD_LIBCSC_EMPTY_COMPOSITE_EXCEPTION_H
#define GUARD_LIBCSC_EMPTY_COMPOSITE_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc
{
namespace exceptions
{
class EmptyCompositeException : public CSCExceptionBase
{
public:
	EmptyCompositeException( const basar::ExceptInfo & sInfo );
	virtual ~EmptyCompositeException();

private:
	EmptyCompositeException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_EMPTY_COMPOSITE_EXCEPTION_H
