#ifndef GUARD_LIBCSC_IBT_I_BOOKING_COMPLETED_CHECKER_H
#define GUARD_LIBCSC_IBT_I_BOOKING_COMPLETED_CHECKER_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace ibt
{
class IBookingCompletedChecker
{
public:
	virtual ~IBookingCompletedChecker() {}	

	virtual bool isIBTBookingCompleted( const basar::Int16 branchNo, const basar::Int32 orderNo/*, const basar::Int32 orderLineNo = 0*/) const = 0;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_BOOKING_COMPLETED_CHECKER_H
