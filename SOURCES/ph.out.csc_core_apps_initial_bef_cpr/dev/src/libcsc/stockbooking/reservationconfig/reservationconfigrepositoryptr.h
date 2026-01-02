#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATIONCONFIG_REPOSITORY_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATIONCONFIG_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class ReservationConfigRepository;
typedef boost::shared_ptr<ReservationConfigRepository> ReservationConfigRepositoryPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATIONCONFIG_REPOSITORY_PTR_H
