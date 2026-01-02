#include <customer/orderinfo/orderinfosqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace customer {

OrderInfoSqlMapper::OrderInfoSqlMapper(OrderInfoPtr orderInfo, const basar::db::sql::ResultsetRef resultSet) :
	OrderInfoMapperBase(orderInfo),
	m_ResultSet(resultSet)
{
}

OrderInfoSqlMapper::~OrderInfoSqlMapper()
{
}

const basar::VarString OrderInfoSqlMapper::getSelectSQL(const basar::Int16 branchNo,
	const basar::Date& orderDate, const basar::Int32 customerNo, const basar::Int32 articleNo)
{
	basar::Int32 today = basar::Date::getCurrent().getDate();
	std::stringstream sql;
	sql << "SELECT "
				"AAUF.filialnr AS branchno, " 
				"AAUF.datum AS orderdate, "
				"AAUF.idfnr AS customerno, "
				"APOS.kdauftragbestellnr AS referenceno, "
				"AAUF.kdauftragnr AS orderno, "
				"APOS.artikel_nr AS articleno, "
				"APOS.mengebestaetigt AS quantityconfirmed, "
				"APOS.mengebestellt AS quantityordered, "
				"AAUF.kdauftragart AS ordertype "
			"FROM akdauftrag AAUF "
				"JOIN akdauftragpos APOS ON AAUF.kdauftragnr = APOS.kdauftragnr AND AAUF.datum = APOS.datum "
			"WHERE "
				"AAUF.filialnr = " << branchNo << " AND "
				"AAUF.datum = " << orderDate.getDate() << " ";
	if (customerNo > 0)
	{
		sql << "AND AAUF.idfnr = " << customerNo << " ";
	}
	if (articleNo > 0)
	{
		sql << "AND APOS.artikel_nr = " << articleNo << " ";
	}
	sql <<	"UNION "
			"SELECT "
				"AUF.filialnr AS branchno, " 
				<< today << " AS orderdate, "
				"AUF.idfnr AS customerno, " 
				"POS.kdauftragbestellnr AS referenceno, " 
				"AUF.kdauftragnr AS orderno, " 
				"POS.artikel_nr AS articleno, " 
				"POS.mengebestaetigt AS quantityconfirmed, " 
				"POS.mengebestellt AS quantityordered, " 
				"AUF.kdauftragart AS ordertype "
			"FROM kdauftrag AUF "
				"JOIN kdauftragpos POS ON AUF.kdauftragnr = POS.kdauftragnr "
			"WHERE "
				"AUF.filialnr = " << branchNo << " AND "
				<< today << " = " << orderDate.getDate() << " ";
	if (customerNo > 0)
	{
		sql << "AND AUF.idfnr = " << customerNo << " ";
	}
	if (articleNo > 0)
	{
		sql << "AND POS.artikel_nr = " << articleNo << " ";
	}

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}

void OrderInfoSqlMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo					(m_ResultSet.getInt16("branchno"));
	setCustomerNo				(m_ResultSet.getInt32("customerno"));
	setOrderNo					(m_ResultSet.getInt32("orderno"));
	setOrderDate				(m_ResultSet.getInt32("orderdate"));
	setOrderType				(m_ResultSet.getString("ordertype"));

	setArticleNo				(m_ResultSet.getInt32("articleno"));
	setQuantityOrdered			(m_ResultSet.getInt32("quantityordered"));
	setQuantityConfirmed		(m_ResultSet.getInt32("quantityconfirmed"));
	setReferenceNo				(m_ResultSet.getString("referenceno"));
}


} // end namespace customer
} // end namespace libcsc

