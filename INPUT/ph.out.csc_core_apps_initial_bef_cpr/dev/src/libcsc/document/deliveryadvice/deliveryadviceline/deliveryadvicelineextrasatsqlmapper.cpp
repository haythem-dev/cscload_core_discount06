#include "deliveryadvicelineextrasatsqlmapper.h"
#include "deliveryadvicelineextrasat.h"
#include <libbasarcmnutil_date.h>
#include <logger/loggerpool.h>

namespace libcsc {
namespace document {

DeliveryAdviceLineExtrasATSQLMapper::DeliveryAdviceLineExtrasATSQLMapper(DeliveryAdviceLineExtrasATPtr deliveryAdviceLineExtrasAT, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceLineExtrasATMapperBase(deliveryAdviceLineExtrasAT),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceLineExtrasATSQLMapper::~DeliveryAdviceLineExtrasATSQLMapper()
{
}

const basar::VarString DeliveryAdviceLineExtrasATSQLMapper::getSelectSQL( const basar::VarString & dbName,
															const basar::Int16 branchNo,
															const basar::Int32 customerNo,
															const basar::Date& deliveryAdviceDate,
															const basar::Int32 pharmosOrderNo,
															const basar::Int32 pharmosOrderPosNo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineExtrasATSQLMapper::getSelectSQL()");

	std::stringstream sSql;

	sSql <<
		"SELECT "
		"l.branchno, "
		"l.customerno, "
		"l.deliveryadvicedate, "
		"l.pharmosorderno, "
		"l.pharmosorderposno, "
		"l.deliveryadviceposno, "
		"CASE WHEN bitand(az.etartklasse1, 512 ) = 512 THEN 1 ELSE 0 END AS isnarcotic, "
		"CASE WHEN bitand(az.etartklasse1, 2048 ) = 2048 THEN 1 ELSE 0 END AS isrx, "
		"CASE WHEN az.kzpsychostoffe IN ('J', 'P', 'B', 'C', 'D', 'E', 'F', 'T') THEN 1 ELSE 0 END AS ispsychotropic, "
		"CASE WHEN bitand(az.etartklasse1, 256 ) = 256 THEN 1 ELSE 0 END AS isveterinary, "
		"CASE WHEN bitand(az.etartschalter4, 1 ) = 1 THEN 1 ELSE 0 END AS ishazardous, "
		"CASE WHEN bitand(az.etartschalter2, 32768 ) = 32768 THEN 1 ELSE 0 END AS isreportable, "
		"CASE WHEN bitand(az.etartschalter2, 8192 ) = 8192 THEN 1 ELSE 0 END AS isshortexpiry "
		"FROM " << dbName << ":deliveryadviceline l "
		"LEFT JOIN artikelzentral az ON az.artikel_nr = articleno "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and pharmosorderno = " << pharmosOrderNo << " and pharmosorderposno =" << pharmosOrderPosNo;
	return sSql.str();
}

const basar::VarString DeliveryAdviceLineExtrasATSQLMapper::getSelectSQL(
    const basar::VarString & dbName,
    const basar::Int16 branchNo,
    const basar::Int32 customerNo,
    const basar::Date& deliveryAdviceDate,
    const basar::VarString deliveryAdviceNo,
    const basar::Int32 deliveryAdvicePosNo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineExtrasATSQLMapper::getSelectSQL()");

    std::stringstream sSql;

    sSql <<
        "SELECT "
        "l.branchno, "
        "l.customerno, "
        "l.deliveryadvicedate, "
        "l.pharmosorderno, "
        "l.pharmosorderposno, "
        "l.deliveryadviceposno, "
		"CASE WHEN bitand(az.etartklasse1, 512 ) = 512 THEN 1 ELSE 0 END AS isnarcotic, "
		"CASE WHEN bitand(az.etartklasse1, 2048 ) = 2048 THEN 1 ELSE 0 END AS isrx, "
		"CASE WHEN az.kzpsychostoffe IN ('J', 'P', 'B', 'C', 'D', 'E', 'F', 'T') THEN 1 ELSE 0 END AS ispsychotropic, "
		"CASE WHEN bitand(az.etartklasse1, 256 ) = 256 THEN 1 ELSE 0 END AS isveterinary, "
		"CASE WHEN bitand(az.etartschalter4, 1 ) = 1 THEN 1 ELSE 0 END AS ishazardous, "
		"CASE WHEN bitand(az.etartschalter2, 32768 ) = 32768 THEN 1 ELSE 0 END AS isreportable, "
		"CASE WHEN bitand(az.etartschalter2, 8192 ) = 8192 THEN 1 ELSE 0 END AS isshortexpiry "
        "FROM " << dbName << ":deliveryadviceline l "
		"LEFT JOIN artikelzentral az ON az.artikel_nr = articleno "
        "WHERE "
        << " l.branchno = " << branchNo << " and l.customerno = " << customerNo
        << " and l.deliveryadvicedate = " << deliveryAdviceDate.getDate()
        << " and l.deliveryadviceno = " << deliveryAdviceNo
        << " and l.deliveryadviceposno = " << deliveryAdvicePosNo;
    return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceLineExtrasATSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineExtrasATSQLMapper::doMap()");

	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo( m_ResultSet.getInt16("branchno") );
	setCustomerNo( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate( basar::Date(m_ResultSet.getInt32("deliveryadvicedate") ));
	setPharmosOrderNo( m_ResultSet.getInt32("pharmosorderno") );
	setPharmosOrderPosNo( m_ResultSet.getInt32("pharmosorderposno") );
	setDeliveryPosNo( m_ResultSet.getInt32("deliveryadviceposno") );

	setIsNarcotic( m_ResultSet.getInt32("isnarcotic") == 1 );
	setIsRX(m_ResultSet.getInt32("isrx") == 1 );
	setIsPsychotropic( m_ResultSet.getInt32("ispsychotropic") == 1 );
	setIsVeterinary( m_ResultSet.getInt32("isveterinary") == 1 );
	setIsHazardous( m_ResultSet.getInt32("ishazardous") == 1 );
	setIsReportable( m_ResultSet.getInt32("isreportable") == 1);
	setIsShortExpiry( m_ResultSet.getInt32("isshortexpiry") == 1 );
}

} // end namespace document
} // end namespace libcsc
