#include <customer/customercondition/customerconditionsqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc {
namespace customer {

CustomerConditionSqlMapper::CustomerConditionSqlMapper(CustomerConditionPtr cuco, const basar::db::sql::ResultsetRef resultSet) :
	CustomerConditionMapperBase(cuco),
	m_ResultSet(resultSet)
{
}

CustomerConditionSqlMapper::~CustomerConditionSqlMapper()
{
}

const basar::VarString CustomerConditionSqlMapper::getSelectSQL(const basar::Int16 branchNo,
	const basar::Int32 customerNoFrom, const basar::Int32 articleNoFrom,
	const basar::Int32 maxPriceElements, const basar::Int32 customerNoFilter)
{
	std::stringstream sql;
	sql << "SELECT FIRST " << maxPriceElements + 1 << " "
				"cc.branchno AS branchno, "
				"cc.customerno AS customerno, "
				"cc.articleno AS articleno, "
				"cc.baseqty AS basequantity, "
				"cc.preisekapo AS pharmacypurchaseprice, "
				"cc.discountvaluepct AS discountpercentage, "
				"cc.discountprice AS discountprice, "
				"cc.payterm1 AS paymentdays1, "
				"cc.discountpct1 AS discountpercentage1, "
				"cc.discountprice1 AS discountprice1, "
				"cc.payterm2 AS paymentdays2, "
				"cc.discountpct2 AS discountpercentage2, "
				"cc.discountprice2 AS discountprice2, "
				"cc.payterm3 AS paymentdays3, "
				"cc.discountpct3 AS discountpercentage3, "
				"cc.discountprice3 AS discountprice3, "
				"cc.payterm4 AS paymentdays4, "
				"cc.discountpct4 AS discountpercentage4, "
				"cc.discountprice4 AS discountprice4, "
				"cc.payterm5 AS paymentdays5, "
				"cc.discountpct5 AS discountpercentage5, "
				"cc.discountprice5 AS discountprice5, "
				"cc.payterm6 AS paymentdays6, "
				"cc.discountpct6 AS discountpercentage6, "
				"cc.discountprice6 AS discountprice6 "
			"FROM "
				"cucosserbia cc "
			"WHERE "
				"cc.branchno = " << branchNo << " AND ";
	if (customerNoFilter > 0)
	{
		sql <<	"cc.customerno = " << customerNoFilter << " AND cc.articleno >= " << articleNoFrom << " ";
	}
	else
	{
		sql <<	"((cc.customerno >= " << customerNoFrom << " AND cc.articleno >= " << articleNoFrom << ") OR (cc.customerno > " << customerNoFrom << ")) ";
	}
	sql <<	"ORDER BY "
				"cc.customerno, "
				"cc.articleno";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}

void CustomerConditionSqlMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo					(m_ResultSet.getInt16("branchno"));
	setCustomerNo				(m_ResultSet.getInt32("customerno"));
	setArticleNo				(m_ResultSet.getInt32("articleno"));
	setBaseQuantity				(m_ResultSet.getInt32("basequantity"));
	setPharmacyPurchasePrice	(m_ResultSet.getDecimal("pharmacypurchaseprice"));
	setDiscountPercentage		(m_ResultSet.getDecimal("discountpercentage"));
	setDiscountPrice			(m_ResultSet.getDecimal("discountprice"));

	setPTPaymentDays1			(m_ResultSet.getInt16("paymentdays1"));
	setPTDiscountPercentage1	(m_ResultSet.getDecimal("discountpercentage1"));
	setPTDiscountPrice1			(m_ResultSet.getDecimal("discountprice1"));

	setPTPaymentDays2			(m_ResultSet.getInt16("paymentdays2"));
	setPTDiscountPercentage2	(m_ResultSet.getDecimal("discountpercentage2"));
	setPTDiscountPrice2			(m_ResultSet.getDecimal("discountprice2"));

	setPTPaymentDays3			(m_ResultSet.getInt16("paymentdays3"));
	setPTDiscountPercentage3	(m_ResultSet.getDecimal("discountpercentage3"));
	setPTDiscountPrice3			(m_ResultSet.getDecimal("discountprice3"));

	setPTPaymentDays4			(m_ResultSet.getInt16("paymentdays4"));
	setPTDiscountPercentage4	(m_ResultSet.getDecimal("discountpercentage4"));
	setPTDiscountPrice4			(m_ResultSet.getDecimal("discountprice4"));

	setPTPaymentDays5			(m_ResultSet.getInt16("paymentdays5"));
	setPTDiscountPercentage5	(m_ResultSet.getDecimal("discountpercentage5"));
	setPTDiscountPrice5			(m_ResultSet.getDecimal("discountprice5"));

	setPTPaymentDays6			(m_ResultSet.getInt16("paymentdays6"));
	setPTDiscountPercentage6	(m_ResultSet.getDecimal("discountpercentage6"));
	setPTDiscountPrice6			(m_ResultSet.getDecimal("discountprice6"));
}


} // end namespace customer
} // end namespace libcsc

