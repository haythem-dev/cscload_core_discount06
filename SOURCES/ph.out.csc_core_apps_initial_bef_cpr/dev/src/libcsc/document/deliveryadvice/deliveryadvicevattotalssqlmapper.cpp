#include "deliveryadvicevattotalssqlmapper.h"
#include "deliveryadvicevattotals.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace document {

DeliveryAdviceVatTotalsSQLMapper::DeliveryAdviceVatTotalsSQLMapper(DeliveryAdviceVatTotalsPtr deliveryAdviceVatTotals, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceVatTotalsMapperBase(deliveryAdviceVatTotals),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceVatTotalsSQLMapper::~DeliveryAdviceVatTotalsSQLMapper()
{
}

const basar::VarString DeliveryAdviceVatTotalsSQLMapper::getSelectSQL(
	const basar::VarString& dbName,
	const basar::Int16 branchNo,
	const basar::Int32 customerNo,
	const basar::Date& deliveryAdviceDate,
	const basar::VarString& deliveryAdviceNo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceVatTotalsSQLMapper::getSelectSQL()");
	std::stringstream sSql;

	sSql <<
		"SELECT "
			"branchno, "
			"customerno, "
			"deliveryadvicedate, "
			"deliveryadviceno, "
			"vat, "
			"NVL(vatpercentage, 0.0) AS vatpercentage, "
			"NVL(netvalue,0.0) AS netvalue, "
			"NVL(vatvalue,0.0) AS vatvalue, "
			"sumlinefee, "
			"sumpackagefee "
			"FROM " << dbName << ":deliveryadvicevattotals "
			"WHERE "
			"branchno=" << branchNo << " AND "
			"customerno=" << customerNo << " AND "
			"deliveryadvicedate=" << deliveryAdviceDate.getDate() << " AND "
			"deliveryadviceno='" << deliveryAdviceNo << "'";
	return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceVatTotalsSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceVatTotalsSQLMapper::doMap()");
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo				(m_ResultSet.getInt16("branchno"));
	setCustomerNo			(m_ResultSet.getInt32("customerno"));
	setDeliveryAdviceDate	(basar::Date(m_ResultSet.getInt32("deliveryadvicedate")));
	setDeliveryAdviceNo		(m_ResultSet.getString("deliveryadviceno"));

	setVat					(m_ResultSet.getString("vat"));

	setVatPercentage		(m_ResultSet.getDecimal("vatpercentage"));
	setNetValue				(m_ResultSet.getDecimal("netvalue"));
	setVatValue				(m_ResultSet.getDecimal("vatvalue"));
	setSumLineFee			(m_ResultSet.getDecimal("sumlinefee"));
	setSumPackageFee		(m_ResultSet.getDecimal("sumpackagefee"));
}

} // end namespace document
} // end namespace libcsc
