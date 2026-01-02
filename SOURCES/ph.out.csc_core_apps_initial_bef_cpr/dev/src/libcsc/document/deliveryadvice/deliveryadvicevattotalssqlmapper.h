#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSSQLMAPPER_H

#include "deliveryadvicevattotalsmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceVatTotalsSQLMapper : public DeliveryAdviceVatTotalsMapperBase
{
public:
	DeliveryAdviceVatTotalsSQLMapper(DeliveryAdviceVatTotalsPtr deliveryAdviceVatTotals, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceVatTotalsSQLMapper();

	static const basar::VarString getSelectSQL(const basar::VarString& dbName,
												const basar::Int16 branchNo,
												const basar::Int32 customerNo, 
												const basar::Date& deliveryAdviceDate, 
												const basar::VarString& deliveryAdviceNo);

protected:
	virtual void doMap();

private:
	DeliveryAdviceVatTotalsSQLMapper(const DeliveryAdviceVatTotalsSQLMapper&);
	DeliveryAdviceVatTotalsSQLMapper & operator=(const DeliveryAdviceVatTotalsSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSSQLMAPPER_H
