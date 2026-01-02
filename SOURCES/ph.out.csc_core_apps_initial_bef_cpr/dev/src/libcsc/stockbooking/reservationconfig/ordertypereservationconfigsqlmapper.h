#ifndef GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATION_CONFIGSQLMAPPER_H
#define GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATION_CONFIGSQLMAPPER_H

#include <stockbooking/reservationconfig/ordertypereservationconfigmapperbase.h>
#include <stockbooking/reservationconfig/iordertypereservationconfigptr.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace stockbooking {

class OrderTypeReservationConfigSQLMapper : public OrderTypeReservationConfigMapperBase
{
public:
	OrderTypeReservationConfigSQLMapper(OrderTypeReservationConfigPtr orderTypeReservationConfig, const basar::db::sql::ResultsetRef resultSet);
	virtual ~OrderTypeReservationConfigSQLMapper();

	static const basar::VarString getSelectSQL();
	static const basar::VarString getSelectSQLById(const basar::Int32& id);
	static const basar::VarString getSelectSQLByOrderType(const basar::VarString& orderType);
	static const basar::VarString getUpdateSQL(const IOrderTypeReservationConfigPtr orderTypeReservationConfig );
	static const basar::VarString getInsertSQL(const IOrderTypeReservationConfigPtr orderTypeReservationConfig );
	static const basar::VarString getDeleteSQL( const basar::Int32& id );


protected:
	virtual void doMap();

private:
	OrderTypeReservationConfigSQLMapper(const OrderTypeReservationConfigSQLMapper&);
	OrderTypeReservationConfigSQLMapper & operator=(const OrderTypeReservationConfigSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATION_CONFIGSQLMAPPER_H
