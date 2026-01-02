#ifndef GUARD_LIBCSC_PROPERTY_UNSET_EXCEPTION_H
#define GUARD_LIBCSC_PROPERTY_UNSET_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc
{
namespace exceptions
{
class PropertyUnsetException : public CSCExceptionBase
{
public:
	PropertyUnsetException( const basar::ExceptInfo & sInfo );
	virtual ~PropertyUnsetException();

private:
	PropertyUnsetException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_PROPERTY_UNSET_EXCEPTION_H
