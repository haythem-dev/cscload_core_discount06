#include "deliveryadvicelinedetailssqlmapper.h"
#include "deliveryadvicelinedetails.h"
#include <libbasarcmnutil_date.h>
#include <logger/loggerpool.h>

namespace libcsc {
namespace document {

DeliveryAdviceLineDetailsSQLMapper::DeliveryAdviceLineDetailsSQLMapper(DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceLineDetailsMapperBase(deliveryAdviceLineDetails),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceLineDetailsSQLMapper::~DeliveryAdviceLineDetailsSQLMapper()
{
}

const basar::VarString DeliveryAdviceLineDetailsSQLMapper::getSelectSQL( const basar::VarString & dbName,
															const basar::Int16 branchNo,
															const basar::Int32 customerNo,
															const basar::Date& deliveryAdviceDate,
															const basar::Int32 pharmosOrderNo,
															const basar::Int32 pharmosOrderPosNo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineDetailsSQLMapper::getSelectSQL()");

	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"pharmosorderno, "
		"pharmosorderposno, "
		"deliveryposno, "
		"qty_delivery, "
		"batch, "
		"expirydate, "
		"packageid, "
		"trackingid, "
		"qty_lack, "
		"precalcbatchchanged "
		"FROM " << dbName << ":deliveryadvicelinedetails "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and pharmosorderno = " << pharmosOrderNo << " and pharmosorderposno =" << pharmosOrderPosNo;
	return sSql.str();
}

const basar::VarString DeliveryAdviceLineDetailsSQLMapper::getSelectSQL(
    const basar::VarString & dbName,
    const basar::Int16 branchNo,
    const basar::Int32 customerNo,
    const basar::Date& deliveryAdviceDate,
    const basar::VarString deliveryAdviceNo,
    const basar::Int32 deliveryAdvicePosNo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineDetailsSQLMapper::getSelectSQL()");

    std::stringstream sSql;

    sSql <<
        "SELECT "
        "ald.branchno, "
        "ald.customerno, "
        "ald.deliveryadvicedate, "
        "ald.pharmosorderno, "
        "ald.pharmosorderposno, "
        "ald.deliveryposno, "
        "ald.qty_delivery, "
        "ald.batch, "
        "ald.expirydate, "
        "ald.packageid, "
        "ald.trackingid, "
        "ald.qty_lack, "
        "ald.precalcbatchchanged "
        "FROM " << dbName << ":deliveryadvicelinedetails ald "
        "inner join " << dbName << ":deliveryadviceline al "
        "  on  al.branchno = ald.branchno and al.customerno = ald.customerno "
        "  and al.deliveryadvicedate = ald.deliveryadvicedate and al.pharmosorderno = ald.pharmosorderno "
        "  and al.pharmosorderposno = ald.pharmosorderposno "
        "WHERE "
        << " ald.branchno = " << branchNo << " and ald.customerno = " << customerNo
        << " and ald.deliveryadvicedate = " << deliveryAdviceDate.getDate()
        << " and al.deliveryadviceno = " << deliveryAdviceNo
        << " and al.deliveryadviceposno = " << deliveryAdvicePosNo;
    return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceLineDetailsSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineDetailsSQLMapper::doMap()");

	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo( m_ResultSet.getInt16("branchno") );
	setCustomerNo( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate( basar::Date(m_ResultSet.getInt32("deliveryadvicedate") ));
	setPharmosOrderNo( m_ResultSet.getInt32("pharmosorderno") );
	setPharmosOrderPosNo( m_ResultSet.getInt32("pharmosorderposno") );
	setDeliveryPosNo( m_ResultSet.getInt32("deliveryposno") );

	setQuantityDelivery( m_ResultSet.getInt32("qty_delivery") );
	setBatch(m_ResultSet.getString("batch") );
	setExpiryDate( basar::Date(m_ResultSet.getInt32("expirydate")) );
	setPackageId( m_ResultSet.getInt32("packageid") );
	setTrackingId( m_ResultSet.getString("trackingid") );
	setQuantityLack( m_ResultSet.getInt32("qty_lack"));
	setPreCalcBatchChanged( m_ResultSet.getInt16("precalcbatchchanged") );
}

} // end namespace document
} // end namespace libcsc
