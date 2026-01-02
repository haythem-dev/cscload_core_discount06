#ifndef GUARD_LIBCSC_CUSTOMER_ORDERINFOSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_ORDERINFOSQLMAPPER_H

#include <customer/orderinfo/orderinfomapperbase.h>

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class OrderInfoSqlMapper : public OrderInfoMapperBase
{
public:
	OrderInfoSqlMapper(
        OrderInfoPtr articleInfo, 
        const basar::db::sql::ResultsetRef resultSet 
            );
    virtual ~OrderInfoSqlMapper();

	static const basar::VarString getSelectSQL(const basar::Int16 branchNo,
		const basar::Date& orderDate, const basar::Int32 customerNo, const basar::Int32 articleNo);

protected:
	virtual void doMap();

private:
	OrderInfoSqlMapper(const OrderInfoSqlMapper&);
	OrderInfoSqlMapper& operator=(const OrderInfoSqlMapper&);
    
    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERINFOSQLMAPPER_H
