#ifndef GUARD_LIBCSC_STOCKBOOKING_I_RESERVATION_REPOSITORY_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_RESERVATION_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class IReservationRepository;
typedef boost::shared_ptr<IReservationRepository> IReservationRepositoryPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_RESERVATION_REPOSITORY_PTR_H
