#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPE_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPE_H

#include <stockbooking/reservationconfig/ireservationtype.h>
#include <datatypes/int32.h>
#include <datatypes/boolean.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace stockbooking {

class ReservationType : public IReservationType
{
	friend class ReservationTypeMapperBase;

public:
	ReservationType();
	virtual ~ReservationType();

	virtual const basar::Int32&			getId() const;
	virtual const basar::Int32&			getReservationType() const;
	virtual const bool&					getWithPharmacyGroup() const;
	virtual const basar::VarString&		getReservationName() const;

private:
	libcsc::Int32						m_Id;
	libcsc::Int32						m_ReservationType;
	libcsc::Bool						m_WithPharmacyGroup;
	libcsc::VarString					m_ReservationName;
};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPE_H
