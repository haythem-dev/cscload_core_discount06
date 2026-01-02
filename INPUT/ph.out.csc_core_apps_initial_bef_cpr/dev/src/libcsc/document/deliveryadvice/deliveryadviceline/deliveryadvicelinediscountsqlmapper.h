#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDISCOUNTSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDISCOUNTSQLMAPPER_H

#include "deliveryadvicelinediscountmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineDiscountSQLMapper : public DeliveryAdviceLineDiscountMapperBase
{
public:
	DeliveryAdviceLineDiscountSQLMapper(DeliveryAdviceLineDiscountPtr deliveryAdviceLineDiscount, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceLineDiscountSQLMapper();

	static const basar::VarString getSelectSQL( const basar::VarString & dbName, 
												const basar::Int16 branchNo, 
												const basar::Int32 customerNo, 
												const basar::Date& deliveryAdviceDate, 
												const basar::Int32 pharmosOrderNo, 
												const basar::Int32 pharmosOrderPosNo );

protected:
	virtual void doMap();

private:
	DeliveryAdviceLineDiscountSQLMapper(const DeliveryAdviceLineDiscountSQLMapper&);
	DeliveryAdviceLineDiscountSQLMapper & operator=(const DeliveryAdviceLineDiscountSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDISCOUNTSQLMAPPER_H
