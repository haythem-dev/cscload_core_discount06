#ifndef GUARD_LIBCSC_EMPTY_COLLECTION_EXCEPTION_H
#define GUARD_LIBCSC_EMPTY_COLLECTION_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc
{
namespace exceptions
{
class EmptyCollectionException : public CSCExceptionBase
{
public:
	EmptyCollectionException( const basar::ExceptInfo & sInfo );
	virtual ~EmptyCollectionException();

private:
	EmptyCollectionException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_EMPTY_COLLECTION_EXCEPTION_H
