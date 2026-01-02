#ifndef GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_MAPPER_BASE_H
#define GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "ordertypereservationconfigpharmacygroupptr.h"

namespace libcsc {
namespace stockbooking {

class OrderTypeReservationConfigPharmacyGroupMapperBase
{
public:
	OrderTypeReservationConfigPharmacyGroupMapperBase(OrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup);

	void			map();
protected:
	virtual ~OrderTypeReservationConfigPharmacyGroupMapperBase();

	virtual void	doMap() = 0;

	void setId( const basar::Int32& id );
	void setPharmcyGroupId( const basar::VarString& pharmcyGroupId );
	void setOrderTypeReservationConfigId(const basar::Int32 OrderTypeReservationConfigId );
	
private:
	OrderTypeReservationConfigPharmacyGroupPtr m_OrderTypeReservationConfigPharmacyGroup;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_MAPPER_BASE_H
