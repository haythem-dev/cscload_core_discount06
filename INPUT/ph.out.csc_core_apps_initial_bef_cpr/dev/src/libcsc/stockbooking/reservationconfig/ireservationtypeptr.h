#ifndef GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONTYPE_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONTYPE_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace stockbooking {

class IReservationType;
typedef boost::shared_ptr<IReservationType> IReservationTypePtr;

typedef std::vector<IReservationTypePtr> IReservationTypeCollection;

typedef boost::shared_ptr<IReservationTypeCollection> IReservationTypeCollectionPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONTYPE_PTR_H
