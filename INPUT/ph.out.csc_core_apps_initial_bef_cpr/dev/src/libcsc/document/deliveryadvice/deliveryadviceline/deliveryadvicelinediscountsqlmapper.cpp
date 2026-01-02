#include "deliveryadvicelinediscountsqlmapper.h"
#include "deliveryadvicelinediscount.h"
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace document {

DeliveryAdviceLineDiscountSQLMapper::DeliveryAdviceLineDiscountSQLMapper(DeliveryAdviceLineDiscountPtr deliveryAdviceLineDiscount, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceLineDiscountMapperBase(deliveryAdviceLineDiscount),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceLineDiscountSQLMapper::~DeliveryAdviceLineDiscountSQLMapper()
{
}

const basar::VarString DeliveryAdviceLineDiscountSQLMapper::getSelectSQL( const basar::VarString & dbName, 
															const basar::Int16 branchNo, 
															const basar::Int32 customerNo, 
															const basar::Date& deliveryAdviceDate, 
															const basar::Int32 pharmosOrderNo, 
															const basar::Int32 pharmosOrderPosNo )
{
	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"pharmosorderno, "
		"pharmosorderposno, "
		"discountmode, "
		"discount, "
		"origin, "
		"deletereason, "
		"discountvalue, "
		"discounttype, "
		"hierarchy, "
		"calculationbasis, "
		"NVL(cdf.active_flag, 0)::smallint AS active_flag, "
		"NVL(cdf.kindofdiscount, 0)::smallint AS kindofdiscount, "
		"NVL(cdf.name, ' ') AS discountmodename "
		"FROM " << dbName << ":deliveryadvicelinediscounts as daldi "
		"LEFT JOIN " << dbName << ":cdiscform as cdf on (cdf.discountformno == daldi.discountmode) "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and pharmosOrderNo = '" << pharmosOrderNo << "' and pharmosOrderPosNo =" << pharmosOrderPosNo;
	return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceLineDiscountSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo				( m_ResultSet.getInt16("branchno") );
	setCustomerNo			( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate	( basar::Date(m_ResultSet.getInt32("deliveryadvicedate")) );
	setPharmosOrderNo		( m_ResultSet.getInt32("pharmosorderno") );
	setPharmosOrderPosNo	( m_ResultSet.getInt32("pharmosorderposno") );
	
	setDiscountMode			( m_ResultSet.getInt16("discountmode") );
	setDiscountModeName		(m_ResultSet.getString("discountmodename"));

	setDiscount				( m_ResultSet.getDecimal("discount") );
	setOrigin				( m_ResultSet.getString("origin") );
	setDeleteReason			( m_ResultSet.getInt16("deletereason") );
	setDiscountValue		( m_ResultSet.getDecimal("discountvalue") );
	setDiscountType			( m_ResultSet.getInt16("discounttype") );
	setHierarchy			( m_ResultSet.getInt16("hierarchy") );
	setCalculationBasis		( m_ResultSet.getInt16("calculationbasis") );

	enum KindOfDiscountEnum kindOfDiscount = Undefined;
	try
	{
        int cdfActiveFlag = m_ResultSet.getInt16("active_flag");
        if (cdfActiveFlag == 1)
        {
            kindOfDiscount = static_cast<enum KindOfDiscountEnum>(m_ResultSet.getInt16("kindofdiscount"));
        }
    }
	catch (...)
	{
		// e.g. could not map to a KindOfDiscountEnum
		kindOfDiscount = Undefined;
	}

	setKindOfDiscount((const enum KindOfDiscountEnum) kindOfDiscount);
}

} // end namespace document
} // end namespace libcsc
