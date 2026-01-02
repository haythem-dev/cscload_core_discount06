#ifndef GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_SQLMAPPER_H
#define GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_SQLMAPPER_H

#include "ordertypereservationconfigpharmacygroupmapperbase.h"
#include "iordertypereservationconfigpharmacygroupptr.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace stockbooking {

class OrderTypeReservationConfigPharmacyGroupSQLMapper : public OrderTypeReservationConfigPharmacyGroupMapperBase
{
public:
	OrderTypeReservationConfigPharmacyGroupSQLMapper(OrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup, const basar::db::sql::ResultsetRef resultSet);
	virtual ~OrderTypeReservationConfigPharmacyGroupSQLMapper();

	static const basar::VarString getSelectSQLByReservationId(const basar::Int32 reservationId);
	static const basar::VarString getInsertSQL(const IOrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup );
	static const basar::VarString getDeleteSQLById( const basar::Int32 id );
	static const basar::VarString getDeleteSQLByReservationId( const basar::Int32 reservationId );


protected:
	virtual void doMap();

private:
	OrderTypeReservationConfigPharmacyGroupSQLMapper(const OrderTypeReservationConfigPharmacyGroupSQLMapper&);
	OrderTypeReservationConfigPharmacyGroupSQLMapper & operator=(const OrderTypeReservationConfigPharmacyGroupSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_SQLMAPPER_H
