#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINERETURNSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINERETURNSQLMAPPER_H

#include "deliveryadvicelinereturnmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineReturnSQLMapper : public DeliveryAdviceLineReturnMapperBase
{
public:
	DeliveryAdviceLineReturnSQLMapper(DeliveryAdviceLineReturnPtr deliveryAdviceLineReturn, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceLineReturnSQLMapper();

	static const basar::VarString getSelectSQL( const basar::VarString & dbName, 
												const basar::Int16 branchNo, 
												const basar::Int32 customerNo, 
												const basar::Date& deliveryAdviceDate, 
												const basar::VarString &  deliveryAdviceNo,
												const basar::Int32 deliveryAdvicePosNo );

protected:
	virtual void doMap();

private:
	DeliveryAdviceLineReturnSQLMapper( const DeliveryAdviceLineReturnSQLMapper& );
	DeliveryAdviceLineReturnSQLMapper & operator=( const DeliveryAdviceLineReturnSQLMapper& );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINERETURNSQLMAPPER_H
