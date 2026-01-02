#ifndef GUARD_LIBCSC_STOCKBOOKING_CUSTOMER_STOCKRESERVED_SQLMAPPER_H
#define GUARD_LIBCSC_STOCKBOOKING_CUSTOMER_STOCKRESERVED_SQLMAPPER_H

#include "customerstockreservedmapperbase.h"
#include <stockbooking/reservation/icustomerstockreservedptr.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace stockbooking {

class CustomerStockReservedSQLMapper : public CustomerStockReservedMapperBase
{
public:
	CustomerStockReservedSQLMapper(CustomerStockReservedPtr customerStockReserved, const basar::db::sql::ResultsetRef resultSet);
	virtual ~CustomerStockReservedSQLMapper();

	static const basar::VarString getSelectSQL(const basar::VarString & dbName ,const basar::Int16& branchNo, const basar::Int32& articleNo );
	static const basar::VarString getUpdateSQL(const basar::VarString & dbName ,const ICustomerStockReservedPtr customerStockReserved );
	static const basar::VarString getDeleteSQL( const basar::VarString & dbName ,const ICustomerStockReservedPtr customerStockReserved );

protected:
	virtual void doMap();

private:
	CustomerStockReservedSQLMapper(const CustomerStockReservedSQLMapper&);
	CustomerStockReservedSQLMapper & operator=(const CustomerStockReservedSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_CUSTOMER_STOCKRESERVED_SQLMAPPER_H
