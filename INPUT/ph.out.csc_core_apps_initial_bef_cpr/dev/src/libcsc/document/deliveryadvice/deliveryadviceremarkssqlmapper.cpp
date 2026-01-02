#include "deliveryadviceremarkssqlmapper.h"
#include "deliveryadviceremarks.h"
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace document {

DeliveryAdviceRemarksSQLMapper::DeliveryAdviceRemarksSQLMapper(DeliveryAdviceRemarksPtr deliveryAdviceRemarks, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceRemarksMapperBase(deliveryAdviceRemarks),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceRemarksSQLMapper::~DeliveryAdviceRemarksSQLMapper()
{
}

const basar::VarString DeliveryAdviceRemarksSQLMapper::getSelectSQL( const basar::VarString & dbName,
															const basar::Int16 branchNo, 
															const basar::Int32 customerNo, 
															const basar::Date& deliveryAdviceDate, 
															const basar::Int32 cscOrderNo,
															const basar::Int32 cscOrderPosNo)
{
	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"cscorderno, "
		"cscorderposno, "
		"remarktype, "
		"serialno, "
		"remarktext "
		"FROM " << dbName << ":deliveryadviceremark "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and cscorderno = '" << cscOrderNo << "' and cscorderposno =" << cscOrderPosNo;
	return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceRemarksSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo				( m_ResultSet.getInt16("branchno") );
	setCustomerNo			( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate	( basar::Date(m_ResultSet.getInt32("deliveryadvicedate")) );
	setCSCOrderNo			( m_ResultSet.getInt32("cscorderno") );
	setCSCOrderPosNo		(m_ResultSet.getInt32("cscorderposno"));
	setRemarkType			( static_cast< ::OrderRemarkTypeEnum >(m_ResultSet.getInt16("remarktype")) );
	setSerialNo				( m_ResultSet.getInt16("serialno") );
	
	setRemarkText			( m_ResultSet.getString("remarktext") );
}

} // end namespace document
} // end namespace libcsc
