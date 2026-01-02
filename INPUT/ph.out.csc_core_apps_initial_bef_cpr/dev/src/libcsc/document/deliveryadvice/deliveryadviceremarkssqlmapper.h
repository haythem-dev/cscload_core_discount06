#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_SQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_SQLMAPPER_H

#include "deliveryadviceremarksmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceRemarksSQLMapper : public DeliveryAdviceRemarksMapperBase
{
public:
	DeliveryAdviceRemarksSQLMapper(DeliveryAdviceRemarksPtr deliveryAdviceRemark, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceRemarksSQLMapper();

	static const basar::VarString getSelectSQL( const basar::VarString & dbName,
												const basar::Int16 branchNo,
												const basar::Int32 customerNo,
												const basar::Date& deliveryAdviceDate,
												const basar::Int32 cscOrderNo,
												const basar::Int32 cscOrderPosNo);
protected:
	virtual void doMap();

private:
	DeliveryAdviceRemarksSQLMapper(const DeliveryAdviceRemarksSQLMapper&);
	DeliveryAdviceRemarksSQLMapper & operator=(const DeliveryAdviceRemarksSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_SQLMAPPER_H
