#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEEXTRASATSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEEXTRASATSQLMAPPER_H

#include "deliveryadvicelineextrasatmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineExtrasATSQLMapper : public DeliveryAdviceLineExtrasATMapperBase
{
public:
	DeliveryAdviceLineExtrasATSQLMapper(DeliveryAdviceLineExtrasATPtr deliveryAdviceLineExtrasAT, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceLineExtrasATSQLMapper();

	static const basar::VarString getSelectSQL( 
		const basar::VarString & dbName,
		const basar::Int16 branchNo,
		const basar::Int32 customerNo,
		const basar::Date& deliveryAdviceDate,
		const basar::Int32 pharmosOrderNo,
		const basar::Int32 pharmosOrderPosNo );

    static const basar::VarString getSelectSQL(
        const basar::VarString & dbName,
        const basar::Int16 branchNo,
        const basar::Int32 customerNo,
        const basar::Date& deliveryAdviceDate,
        const basar::VarString deliveryAdviceNo,
        const basar::Int32 deliveryAdvicePosNo);

protected:
	virtual void doMap();

private:
	DeliveryAdviceLineExtrasATSQLMapper(const DeliveryAdviceLineExtrasATSQLMapper&);
	DeliveryAdviceLineExtrasATSQLMapper& operator=(const DeliveryAdviceLineExtrasATSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEEXTRASATSQLMAPPER_H
