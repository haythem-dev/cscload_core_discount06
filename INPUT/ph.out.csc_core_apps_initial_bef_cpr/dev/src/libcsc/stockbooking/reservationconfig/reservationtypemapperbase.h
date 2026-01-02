#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPEMAPPER_BASE_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPEMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "reservationtypeptr.h"

namespace libcsc {
namespace stockbooking {

class ReservationTypeMapperBase
{
public:
	ReservationTypeMapperBase(ReservationTypePtr reservationType);

	void			map();
protected:
	virtual ~ReservationTypeMapperBase();

	virtual void	doMap() = 0;

	void setId( const basar::Int32& id );
	void setReservationType( const basar::Int32& reservationType );
	void setWithPharmacyGroup(const basar::Int16& withPharmacyGroup);
	void setReservationName( const basar::VarString& reservationName);

private:
	ReservationTypePtr m_ReservationType;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPEMAPPER_BASE_H
