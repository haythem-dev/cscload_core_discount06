#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDETAILSSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDETAILSSQLMAPPER_H

#include "deliveryadvicelinedetailsmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineDetailsSQLMapper : public DeliveryAdviceLineDetailsMapperBase
{
public:
	DeliveryAdviceLineDetailsSQLMapper(DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceLineDetailsSQLMapper();

	static const basar::VarString getSelectSQL( const basar::VarString & dbName,
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
	DeliveryAdviceLineDetailsSQLMapper(const DeliveryAdviceLineDetailsSQLMapper&);
	DeliveryAdviceLineDetailsSQLMapper & operator=(const DeliveryAdviceLineDetailsSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINESQLMAPPER_H
