#include "reservationtype.h"

namespace libcsc {
namespace stockbooking {

ReservationType::ReservationType()
{
}

ReservationType::~ReservationType()
{
}

const basar::Int32& ReservationType::getId() const
{
	return m_Id;
}

const basar::Int32& ReservationType::getReservationType() const
{
	return m_ReservationType;
}

const bool& ReservationType::getWithPharmacyGroup() const
{
	return m_WithPharmacyGroup;
}

const basar::VarString& ReservationType::getReservationName() const
{
	return m_ReservationName;
}

} // namespace stockbooking
} // namespace libcsc
