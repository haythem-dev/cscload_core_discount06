#ifndef GUARD_LIBCSC_IBT_I_BOOKING_COMPLETED_CHECKER_PTR_H
#define GUARD_LIBCSC_IBT_I_BOOKING_COMPLETED_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
class IBookingCompletedChecker;
typedef boost::shared_ptr<libcsc::ibt::IBookingCompletedChecker> IBookingCompletedCheckerPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_BOOKING_COMPLETED_CHECKER_PTR_H
