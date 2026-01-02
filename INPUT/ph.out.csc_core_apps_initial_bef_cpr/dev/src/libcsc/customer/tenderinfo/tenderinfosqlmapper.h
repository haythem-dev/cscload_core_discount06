#ifndef GUARD_LIBCSC_CUSTOMER_TENDERINFOSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_TENDERINFOSQLMAPPER_H

#include <customer/tenderinfo/tenderinfomapperbase.h>

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class TenderInfoSqlMapper : public TenderInfoMapperBase
{
public:
	TenderInfoSqlMapper(
        TenderInfoPtr tenderInfo, 
        const basar::db::sql::ResultsetRef resultSet 
            );
    virtual ~TenderInfoSqlMapper();

	static const basar::VarString getSelectSQL(const basar::Int16 branchNo,
		const basar::Int32 customerNo, const basar::VarString& contractNo, const basar::Int32 articleNo);

protected:
	virtual void doMap();

private:
	TenderInfoSqlMapper(const TenderInfoSqlMapper&);
	TenderInfoSqlMapper& operator=(const TenderInfoSqlMapper&);
    
    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TENDERINFOSQLMAPPER_H
