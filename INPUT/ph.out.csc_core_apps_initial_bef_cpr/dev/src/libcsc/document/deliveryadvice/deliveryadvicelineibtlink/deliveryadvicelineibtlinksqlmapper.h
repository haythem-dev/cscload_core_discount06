#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINKSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINKSQLMAPPER_H

#include "deliveryadvicelineibtlinkmapperbase.h"
#include <libbasar_definitions.h>
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineIbtLinkSQLMapper : public DeliveryAdviceLineIbtLinkMapperBase
{
public:
	DeliveryAdviceLineIbtLinkSQLMapper(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink, const basar::db::sql::ResultsetRef resultSet);
	virtual ~DeliveryAdviceLineIbtLinkSQLMapper();

    // ===============================================================================================
    // Get SQL statements
    // ===============================================================================================

    static const basar::VarString getSelectSQL(										const basar::VarString& dbName,
																					const basar::Int16 branchNo, 
																					const basar::Int32 customerNo, 
																					const basar::Date& deliveryAdviceDate, 
																					const basar::Int32 cscOrderNo, 
																					const basar::Int32 cscOrderPosNo );

    static const basar::VarString getCustomerOrdersSelectSQL(						const basar::Int16 shuttleBranchNo,
																					const basar::Int32 shuttleOrderNo);

    static const basar::VarString getCustomerOrderDetailsSelectSQL(					const basar::Int16 branchNo,
																					const basar::Int32 customerNo,
																					const basar::Int32 cscOrderNo,
																					const basar::Date& posBookingDate);

	static const basar::VarString getDeliveryAdviceDetails4CustomerOrderSelectSQL(	const basar::VarString& dbName,
																					const basar::Int16 branchNo,
																					const basar::Int32 customerNo,
																					const basar::Int32 cscOrderNo,
																					const basar::Int32 cscOrderPosNo,
																					const basar::Date& deliveryAdviceDate);

    static const basar::VarString getShuttleOrdersSelectSQL(						const basar::Int16 branchNo,
																					const basar::Int32 customerNo,
																					const basar::Int32 cscOrderNo );

	static const basar::VarString getShuttleOrderDetailsSelectSQL(					const basar::Int16 ibtBranchNo,
																					const basar::Int32 ibtCscOrderNo,
																					const basar::Int32 ibtCscOrderPosNo,
																					const basar::Date& ibtDeliveryAdviceDate );

	static const basar::VarString getDeliveryAdviceDetails4ShuttleOrderSelectSQL(	const basar::VarString& dbName,
																					const basar::Int16 branchNo,
																					const basar::Int32 customerNo,
																					const basar::Int32 cscOrderNo,
																					const basar::Int32 cscOrderPosNo,
																					const basar::Date& deliveryAdviceDate,
																					const basar::VarString& deliveryAdviceNo);

    static const basar::VarString getInsertSQL(										const basar::VarString& dbName,
																					const DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink);

protected:
	virtual void doMap();
    virtual void doMapCustomerOrders();
    virtual void doMapCustomerOrderDetails();
    virtual void doMapDeliveryAdvice4CustomerOrder();
    virtual void doMapShuttleOrders();
    virtual void doMapShuttleOrderDetails();
    virtual void doMapDeliveryAdvice4ShuttleOrder();

private:
	DeliveryAdviceLineIbtLinkSQLMapper(const DeliveryAdviceLineIbtLinkSQLMapper&);
	DeliveryAdviceLineIbtLinkSQLMapper & operator=(const DeliveryAdviceLineIbtLinkSQLMapper&);

	const basar::db::sql::ResultsetRef m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINKSQLMAPPER_H
