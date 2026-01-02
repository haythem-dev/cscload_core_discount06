#ifndef GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_MAPPER_BASE_H
#define GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "ordertypereservationconfigptr.h"

namespace libcsc {
namespace stockbooking {

class OrderTypeReservationConfigMapperBase
{
public:
	OrderTypeReservationConfigMapperBase(OrderTypeReservationConfigPtr orderTypeReservationConfig);

	void			map();
protected:
	virtual ~OrderTypeReservationConfigMapperBase();

	virtual void	doMap() = 0;

	void setId( const basar::Int32& id );
	void setReservationType( const basar::Int32 reservationType );
	void setWithPharmacyGroup(const basar::Int16 withPharmacyGroup);
	void setReservationName( const basar::VarString& reservationName );
	void setOrderType(const basar::VarString& orderType);
	void setOrderTypeReservationConfigName(const basar::VarString& orderTypeReservationConfigName);
	void setPriority(const basar::Int16 priority);
	void setReservedStockOnly(const basar::Int16 reservedStockOnly);
	void setFreeStockHasPriority(const basar::Int16 freeStockHasPriority);

private:
	OrderTypeReservationConfigPtr m_OrderTypeReservationConfig;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_MAPPER_BASE_H
