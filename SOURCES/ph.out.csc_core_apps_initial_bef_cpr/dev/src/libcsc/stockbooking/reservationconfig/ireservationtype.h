#ifndef GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONTYPE_H
#define GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONTYPE_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace stockbooking {

class IReservationType
{
public:
	virtual ~IReservationType() {}

	virtual const basar::Int32&			getId() const = 0;
	virtual const basar::Int32&			getReservationType() const = 0;
	virtual const bool&					getWithPharmacyGroup() const = 0;
	virtual const basar::VarString&		getReservationName() const = 0;
};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONTYPE_H
