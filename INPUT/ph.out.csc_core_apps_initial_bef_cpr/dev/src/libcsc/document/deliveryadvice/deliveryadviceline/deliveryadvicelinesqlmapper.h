#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINESQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINESQLMAPPER_H

#include "deliveryadvicelinemapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineSQLMapper : public DeliveryAdviceLineMapperBase
{
public:
	DeliveryAdviceLineSQLMapper(DeliveryAdviceLinePtr deliveryAdviceLine, const DeliveryAdvicePtr& deliveryAdvice, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceLineSQLMapper();

	static const basar::VarString getSelectSQL(
		const basar::VarString& dbName,
		const basar::Int16 branchNo,
		const basar::Int32 customerNo,
		const basar::Date& deliveryAdviceDate,
		const basar::VarString& deliveryAdviceNo,
		const bool onlyInvoicedLines = false);

	static const basar::VarString getSelectSingleSQL(
		const basar::VarString& dbName,
		const basar::Int16 branchNo,
		const basar::Int32 customerNo,
		const basar::Date& deliveryAdviceDate,
		const basar::VarString& deliveryAdviceNo,
		const basar::Int32 deliveryAdvicePosNo);

protected:
	virtual void doMap();

private:
	DeliveryAdviceLineSQLMapper(const DeliveryAdviceLineSQLMapper&);
	DeliveryAdviceLineSQLMapper & operator=(const DeliveryAdviceLineSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINESQLMAPPER_H
