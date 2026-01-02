#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPE_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPE_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace stockbooking {

class ReservationType;
typedef boost::shared_ptr<ReservationType> ReservationTypePtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPE_PTR_H
