#ifndef GUARD_LIBCSC_IBT_BOOKING_COMPLETED_CHECKER_PTR_H
#define GUARD_LIBCSC_IBT_BOOKING_COMPLETED_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
class BookingCompletedChecker;
typedef boost::shared_ptr<libcsc::ibt::BookingCompletedChecker> BookingCompletedCheckerPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_BOOKING_COMPLETED_CHECKER_PTR_H
