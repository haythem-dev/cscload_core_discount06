#ifndef GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONCONFIG_REPOSITORY_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONCONFIG_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class IReservationConfigRepository;
typedef boost::shared_ptr<IReservationConfigRepository> IReservationConfigRepositoryPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONCONFIG_REPOSITORY_PTR_H
