#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONSQLMAPPER_H

#include <customer/customercondition/customerconditionmapperbase.h>

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class CustomerConditionSqlMapper : public CustomerConditionMapperBase
{
public:
	CustomerConditionSqlMapper(
        CustomerConditionPtr cuco, 
        const basar::db::sql::ResultsetRef resultSet 
            );
    virtual ~CustomerConditionSqlMapper();

	static const basar::VarString getSelectSQL(const basar::Int16 branchNo,
		const basar::Int32 customerNoFrom, const basar::Int32 articleNoFrom,
		const basar::Int32 maxPriceElements, const basar::Int32 customerNoFilter);

protected:
	virtual void doMap();

private:
	CustomerConditionSqlMapper(const CustomerConditionSqlMapper&);
	CustomerConditionSqlMapper& operator=(const CustomerConditionSqlMapper&);
    
    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONSQLMAPPER_H
