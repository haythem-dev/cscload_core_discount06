#include "deliveryadvicelineibtlinksqlmapper.h"
#include "deliveryadvicelineibtlink.h"
#include <libbasarcmnutil_date.h>
#include <logger/loggerpool.h>
#include <sstream>

namespace libcsc {
namespace document {

DeliveryAdviceLineIbtLinkSQLMapper::DeliveryAdviceLineIbtLinkSQLMapper(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceLineIbtLinkMapperBase(deliveryAdviceLineIbtLink),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceLineIbtLinkSQLMapper::~DeliveryAdviceLineIbtLinkSQLMapper()
{
}

const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getSelectSQL( const basar::VarString& dbName, 
																		 const basar::Int16 branchNo, 
																		 const basar::Int32 customerNo, 
																		 const basar::Date& deliveryAdviceDate, 
																		 const basar::Int32 cscOrderNo, 
																		 const basar::Int32 cscOrderPosNo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::getSelectSQL()");

	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"deliveryadviceno, "
		"deliveryadviceposno, "
		"cscorderno, "
		"cscorderposno, "
		"ibtbranchno, "
		"ibtcustomerno, "
		"ibtdeliveryadvicedate, "
		"ibtdeliveryadviceno, "
		"ibtdeliveryadviceposno, "
		"ibtcscorderno, "
		"ibtcscorderposno "
		"FROM " << dbName << ":deliveryadvicelineibtlink "
		"WHERE ";

	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and cscorderno = " << cscOrderNo << " and cscorderposno =" << cscOrderPosNo;

	return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceLineIbtLinkSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMap()");

	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo					( m_ResultSet.getInt16("branchno") );
	setCustomerNo				( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate		( basar::Date(m_ResultSet.getInt32("deliveryadvicedate")) );
	setDeliveryAdviceNo			( m_ResultSet.getString("deliveryadviceno") );
	setDeliveryAdvicePosNo		( m_ResultSet.getInt32("deliveryadviceposno") );
	setCscOrderNo				( m_ResultSet.getInt32("cscorderno") );
	setCscOrderPosNo			( m_ResultSet.getInt32("cscorderposno") );
	setIbtBranchNo				( m_ResultSet.getInt16("ibtbranchno") );
	setIbtCustomerNo			( m_ResultSet.getInt32("ibtcustomerno") );
	setIbtDeliveryAdviceDate	( basar::Date(m_ResultSet.getInt32("ibtdeliveryadvicedate")) );
	setIbtDeliveryAdviceNo		( m_ResultSet.getString("ibtdeliveryadviceno") );
	setIbtDeliveryAdvicePosNo	( m_ResultSet.getInt32("ibtdeliveryadviceposno") );
	setIbtCscOrderNo			( m_ResultSet.getInt32("ibtcscorderno") );
	setIbtCscOrderPosNo			( m_ResultSet.getInt32("ibtcscorderposno") );
}

//----------------------------------------------------------------------------------
// Complete Shuttle order step 1: SELECT customer orders by shuttle branch no and shuttle order no
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getCustomerOrdersSelectSQL(
	const basar::Int16 shuttleBranchNo,
	const basar::Int32 shuttleOrderNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::getCustomerOrdersSelectSQL()");

	std::stringstream sql;
 //   sql <<  "select"
 //           " a.kdauftragnr as shuttleorder, p.posnr as shuttleposnr, ireq.branchno as customerbranchno,"
 //           " ireq.customerno as customerno, ireq.cscorderno as customerorderno,"
 //           " ireq.cscorderposno as customerorderposno, pe.datum as bookingdate "
 //           "from kdauftragpos p "
 //           "join kdauftrag a on  a.kdauftragnr = p.kdauftragnr "
 //           "join kdauftragposereignis pe on pe.kdauftragnr = a.kdauftragnr and pe.posnr = p.posnr and pe.posereignisart = 1 "
 //           "join ibtresponse ires on ires.ibtorderno = a.kdauftragnr and ires.ibtorderposno = p.posnr"
 //           " and (cast(to_char(ires.creationdatetime, '%Y%m%d') as integer)) = pe.datum "
 //           "join ibtrequest ireq on ireq.ibtrequestid = ires.ibtrequestid "
 //           "where a.batchschreiben = 1 and a.filialnr = " << shuttleBranchNo << " and a.kdauftragnr = " << shuttleOrderNo;
	sql <<
		"select "
			"ireq.ibtbranchno as ibtbranchno, "
			"ireq.ibtcustomerno as ibtcustomerno, "
			"ires.ibtorderno as shuttleorder, "
			"ires.ibtorderposno as shuttleposnr, "
			"ireq.branchno as customerbranchno, "
			"ireq.customerno as customerno, "
			"ireq.cscorderno as customerorderno, "
			"ireq.cscorderposno as customerorderposno, "
			"pe.datum as bookingdate, "
			"CAST(NVL(k.kdauftragnr, 0) AS INTEGER) as customerorderarchived "
		"from "
			"ibtresponse ires "
			"join ibtrequest ireq on ireq.ibtrequestid = ires.ibtrequestid "
			"join kdauftragposereignis pe on pe.kdauftragnr = ires.ibtorderno and pe.posnr = ires.ibtorderposno and pe.posereignisart = 1 "
				"and (cast(to_char(ires.creationdatetime, '%Y%m%d') as integer)) = pe.datum "
			"left outer join kdauftrag k on ireq.cscorderno = k.kdauftragnr and ireq.customerno = k.idfnr "
		"where "
			"ireq.ibtbranchno = " << shuttleBranchNo << " and "
			"ires.ibtorderno = " << shuttleOrderNo;

	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
    return sql.str();
}

void DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrders()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrders()");

	// TODO: check ResultSet
	if (m_ResultSet.isNull())
	{
		throw;
	}

	setIbtBranchNo(m_ResultSet.getInt16("ibtbranchno"));
	setIbtCustomerNo(m_ResultSet.getInt32("ibtcustomerno"));
	setIbtCscOrderNo(m_ResultSet.getInt32("shuttleorder"));
	setIbtCscOrderPosNo(m_ResultSet.getInt32("shuttleposnr"));
//	setIbtDeliveryAdviceDate(m_ResultSet.getInt32("bookingdate")); // wrong!!!
	setPositionBookingDate(m_ResultSet.getInt32("bookingdate"));
	setBranchNo(m_ResultSet.getInt16("customerbranchno"));
	setCustomerNo(m_ResultSet.getInt32("customerno"));
	setCscOrderNo(m_ResultSet.getInt32("customerorderno"));
	setCscOrderPosNo(m_ResultSet.getInt32("customerorderposno"));
	// TEMP property
	setCustomerOrderArchived(m_ResultSet.getInt32("customerorderarchived") == 0);
}

//----------------------------------------------------------------------------------
// Complete Shuttle order step 2: SELECT delivery advice by branch no, customer no, order no , order position no and delivery advice date
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getDeliveryAdviceDetails4ShuttleOrderSelectSQL(
	const basar::VarString& dbName,
	const basar::Int16 ibtBranchNo,
	const basar::Int32 ibtCustomerNo,
	const basar::Int32 ibtCscOrderNo,
	const basar::Int32 ibtCscOrderPosNo,
	const basar::Date& ibtDeliveryAdviceDate,
	const basar::VarString& ibtDeliveryAdviceNo)
{
	std::stringstream sql;
	sql <<
		"select "
			"h.branchno as ibtbranchno, "
			"h.customerno as ibtcustomerno, "
			"h.deliveryadvicedate as ibtdeliveryadvicedate, "
			"h.deliveryadviceno as ibtdeliveryadviceno, "
			"l.deliveryadviceposno as ibtdeliveryadviceposno, "
			"h.cscorderno as ibtcscorderno, "
			"l.cscorderposno as ibtcscorderposno "
		"from "
			<< dbName << ":deliveryadviceline l "
			"join " << dbName << ":deliveryadvicehead h on h.branchno = l.branchno and h.customerno = l.customerno and "
				"h.deliveryadvicedate = l.deliveryadvicedate and h.deliveryadviceno = l.deliveryadviceno "
		"where "
			"h.branchno = " << ibtBranchNo << " and "
			"h.customerno = " << ibtCustomerNo << " and "
			"h.deliveryadvicedate = " << ibtDeliveryAdviceDate.getDate() << " and "
			"h.deliveryadviceno = '" << ibtDeliveryAdviceNo << "' and "
			"h.cscorderno = " << ibtCscOrderNo << " and "
			"l.cscorderposno = " << ibtCscOrderPosNo;
	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
	return sql.str();
}

void DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4ShuttleOrder()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
		"DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4ShuttleOrder()");

	// TODO: check ResultSet
	if (m_ResultSet.isNull())
	{
		throw;
	}

	setIbtDeliveryAdvicePosNo(m_ResultSet.getInt32("ibtdeliveryadviceposno"));
}

//----------------------------------------------------------------------------------
// Complete Shuttle order step 3: SELECT customer order details by branch no, customer no, order no and order position booking date
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getCustomerOrderDetailsSelectSQL(
	const basar::Int16 branchNo,
	const basar::Int32 customerNo,
	const basar::Int32 cscOrderNo,
	const basar::Date& posBookingDate)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::getCustomerOrderDetailsSelectSQL()");

	std::stringstream sql;
    sql <<
		"select "
			"a.kdauftragnr, "
			"a.kdauftragnrfiliale, "
			"a.rechnungnr, "
			"(cast(to_char(current, '%Y%m%d') as integer)) as orderdate "
		"from kdauftrag a "
		"where "
			"a.filialnr = " << branchNo << " and "
			"a.idfnr = " << customerNo << " and "
			"a.kdauftragnr = " << cscOrderNo << " and "
			"a.rechnungnr > 0 "
		"union "
        "select "
			"a.kdauftragnr, "
			"a.kdauftragnrfiliale, "
			"a.rechnungnr, "
			"a.datum as orderdate "
		"from akdauftrag a "
			"join akdauftragereignis ae on " << posBookingDate.getDate() << " between ae.datum and ae.datum_rechnung and ae.kdauftragnr = a.kdauftragnr "
		"where "
			"a.filialnr = " << branchNo << " and "
			"a.idfnr = " << customerNo << " and "
			"a.kdauftragnr = " << cscOrderNo << " and "
			"a.rechnungnr > 0 and "
            "ae.ereignisart = 110";
	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
    return sql.str();
}

void DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrderDetails()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrderDetails()");

	// TODO: check ResultSet
	if (m_ResultSet.isNull())
	{
		throw;
	}

	setDeliveryAdviceDate(m_ResultSet.getInt32("orderdate"));
	basar::VarString deliveryAdviceNo;
	deliveryAdviceNo.itos(m_ResultSet.getInt32("rechnungnr")); // TODO rechnungsnummer lesen aus orderremarks??? Führende Nullen???
	setDeliveryAdviceNo(deliveryAdviceNo);
}


//----------------------------------------------------------------------------------
// SELECT delivery advice by branch no, customer no, order no , order position no and delivery advice date
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getDeliveryAdviceDetails4CustomerOrderSelectSQL(
    const basar::VarString& dbName,
	const basar::Int16 branchNo,
	const basar::Int32 customerNo,
	const basar::Int32 cscOrderNo,
	const basar::Int32 cscOrderPosNo,
	const basar::Date& deliveryAdviceDate)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::getDeliveryAdviceDetailsSelectSQL()");

	std::stringstream sql;
	sql <<
		"select "
			"h.branchno, "
			"h.customerno, "
			"h.deliveryadvicedate, "
			"h.deliveryadviceno, "
			"l.deliveryadviceposno, "
			"h.cscorderno, "
			"l.cscorderposno "
		"from "
			<< dbName << ":deliveryadviceline l "
			"join " << dbName << ":deliveryadvicehead h on h.branchno = l.branchno and h.customerno = l.customerno"
				" and h.deliveryadvicedate = l.deliveryadvicedate and h.deliveryadviceno = l.deliveryadviceno "
		"where "
			"h.branchno = " << branchNo << " and "
			"h.customerno = " << customerNo << " and "
			"h.deliveryadvicedate = " << deliveryAdviceDate.getDate() << " and "
			"h.cscorderno = " << cscOrderNo << " and "
			"l.cscorderposno = " << cscOrderPosNo;
	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
	return sql.str();
}

void DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4CustomerOrder()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
		"DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4CustomerOrder()");

	// TODO: check ResultSet
	if (m_ResultSet.isNull())
	{
		throw;
	}

	setDeliveryAdviceNo(m_ResultSet.getString("deliveryadviceno"));
	setDeliveryAdvicePosNo(m_ResultSet.getInt32("deliveryadviceposno"));
}


//----------------------------------------------------------------------------------
// SELECT shuttle orders by customer branch no, customer no and customer order no
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getShuttleOrdersSelectSQL(
	const basar::Int16 branchNo,
	const basar::Int32 customerNo,
	const basar::Int32 cscOrderNo)
{
	std::stringstream sql;
	sql <<
            "select a.filialnr, a.idfnr, a.kdauftragnr, a.kdauftragnrfiliale, a.rechnungnr, p.posnr,"
            " ireq.ibtbranchno, ireq.ibtcustomerno, ires.ibtorderno, ires.ibtorderposno,"
            " (cast(to_char(ires.creationdatetime, '%Y%m%d') as integer)) as ibtpositioncreation "
            "from kdauftragpos p "
            "join kdauftrag a on a.kdauftragnr = p.kdauftragnr "
            "join kdauftragereignis e on e.kdauftragnr = a.kdauftragnr and e.ereignisart = 110 "
            "join ibtrequest ireq on ireq.branchno = a.filialnr and ireq.cscorderno = a.kdauftragnr and"
            " ireq.cscorderposno = p.posnr "
            "join ibtresponse ires on ires.ibtrequestid = ireq.ibtrequestid "
            "where a.filialnr = " << branchNo << " and a.kdauftragnr = " << cscOrderNo << " and a.idfnr = " << customerNo << " and p.artikel_nr = ireq.articleno"
            " and (cast(to_char(ireq.creationdatetime, '%Y%m%d') as integer)) between e.datum and (cast(to_char(current, '%Y%m%d') as integer)) "
            "order by ires.ibtorderno, ires.ibtorderposno";
	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
	return sql.str();
}

//----------------------------------------------------------------------------------
// SELECT shuttle order details by ibt branch no, ibt order no, ibt order position no, and ibt order position booking date
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getShuttleOrderDetailsSelectSQL(
	const basar::Int16 ibtBranchNo,
	const basar::Int32 ibtCscOrderNo,
	const basar::Int32 ibtCscOrderPosNo,
	const basar::Date& ibtDeliveryAdviceDate)
{
	std::stringstream sql;
	sql <<
			"select (cast(to_char(current,'%Y%m%d') as integer)) as rechnungsdatum, a.filialnr, a.idfnr,"
            " a.kdauftragnr, a.rechnungnr, a.kdauftragnrfiliale, p.posnr, p.artikel_nr "
            "from kdauftragpos p "
            "join kdauftrag a on a.kdauftragnr = p.kdauftragnr "
            "join kdauftragereignis e on e.kdauftragnr = a.kdauftragnr "
            "where a.filialnr = " << ibtBranchNo << " and a.kdauftragnr = " << ibtCscOrderNo << " and p.posnr = " << ibtCscOrderPosNo <<
            " and a.rechnungnr > 0 and a.kdauftragnrfiliale > 0 and e.ereignisart = 110 "
            "union "
            "select a.datum as rechnungsdatum, a.filialnr, a.idfnr, a.kdauftragnr, a.rechnungnr, a.kdauftragnrfiliale,"
            " p.posnr, p.artikel_nr "
            "from akdauftragpos p "
            "join akdauftrag a on a.datum = p.datum and a.kdauftragnr = p.kdauftragnr "
            "join akdauftragereignis e on e.datum_rechnung = a.datum and e.kdauftragnr = a.kdauftragnr "
            "where a.filialnr = " << ibtBranchNo << " and a.kdauftragnr = " << ibtCscOrderNo << " and p.posnr = " << ibtCscOrderPosNo << 
				" and " << ibtDeliveryAdviceDate.getDate() << " between e.datum and e.datum_rechnung"
            " and a.rechnungnr > 0 and a.kdauftragnrfiliale > 0 and e.ereignisart = 110";
	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
	return sql.str();
}

//----------------------------------------------------------------------------------
// INSERT
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceLineIbtLinkSQLMapper::getInsertSQL(
	const basar::VarString& dbName,
	const DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::getInsertSQL()");

	std::stringstream sql;
	sql <<
        "INSERT INTO " << dbName << ":deliveryadvicelineibtlink "
        "("
            "branchno, "
            "customerno, "
            "deliveryadvicedate, "
            "deliveryadviceno, "
            "deliveryadviceposno, "
            "cscorderno, "
            "cscorderposno, "
            "ibtbranchno, "
            "ibtcustomerno, "
            "ibtdeliveryadvicedate, "
            "ibtdeliveryadviceno, "
            "ibtdeliveryadviceposno, "
            "ibtcscorderno, "
            "ibtcscorderposno "
        ") "
        "VALUES "
        "("
		<< deliveryAdviceLineIbtLink->getBranchNo() << ", "
		<< deliveryAdviceLineIbtLink->getCustomerNo() << ", "
		<< deliveryAdviceLineIbtLink->getDeliveryAdviceDate().getDate() << ", '"
		<< deliveryAdviceLineIbtLink->getDeliveryAdviceNo() << "', "
		<< deliveryAdviceLineIbtLink->getDeliveryAdvicePosNo() << ", "
		<< deliveryAdviceLineIbtLink->getCscOrderNo() << ", "
		<< deliveryAdviceLineIbtLink->getCscOrderPosNo() << ", "
		<< deliveryAdviceLineIbtLink->getIbtBranchNo() << ", "
		<< deliveryAdviceLineIbtLink->getIbtCustomerNo() << ", "
		<< deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate().getDate() << ", '"
		<< deliveryAdviceLineIbtLink->getIbtDeliveryAdviceNo() << "', "
		<< deliveryAdviceLineIbtLink->getIbtDeliveryAdvicePosNo() << ", "
		<< deliveryAdviceLineIbtLink->getIbtCscOrderNo() << ", "
		<< deliveryAdviceLineIbtLink->getIbtCscOrderPosNo() << " "
		")";
	LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), sql.str());
    return sql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
//void DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrders(
//    const basar::UInt16 ibtBranchNo, const basar::UInt32 ibtCustomerNo)
//{
//	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrders()");
//
//	// TODO: check ResultSet
//    if (m_ResultSet.isNull())
//    {
//        throw;
//    }
//
//    setIbtBranchNo(ibtBranchNo);
//    setIbtCustomerNo(ibtCustomerNo);
//    setIbtCscOrderNo(m_ResultSet.getInt32("shuttleorder"));
//    setIbtCscOrderPosNo(m_ResultSet.getInt32("shuttleposnr"));
//    setIbtDeliveryAdviceDate(m_ResultSet.getInt32("bookingdate"));
//    setBranchNo(m_ResultSet.getInt16("customerbranchno"));
//    setCustomerNo(m_ResultSet.getInt32("customerno"));
//    setCscOrderNo(m_ResultSet.getInt32("customerorderno"));
//    setCscOrderPosNo(m_ResultSet.getInt32("customerorderposno"));
//}

//void DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrderDetails()
//{
//	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMapCustomerOrderDetails()");
//
//	// TODO: check ResultSet
//    if (m_ResultSet.isNull())
//    {
//        throw;
//    }
//
//    setDeliveryAdviceDate(m_ResultSet.getInt32("orderdate"));
//    basar::VarString deliveryAdviceNo;
//    deliveryAdviceNo.itos(m_ResultSet.getInt32("rechnungnr")); // TODO rechnungsnummer lesen aus orderremarks??? Führende Nullen???
//    setDeliveryAdviceNo(deliveryAdviceNo);
//}

//void DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4CustomerOrder()
//{
//    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
//        "DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4CustomerOrder()");
//
//    // TODO: check ResultSet
//    if (m_ResultSet.isNull())
//    {
//        throw;
//    }
//
//	setDeliveryAdviceNo(m_ResultSet.getString("deliveryadviceno"));
//    setDeliveryAdvicePosNo(m_ResultSet.getInt32("deliveryadviceposno"));
//}

void DeliveryAdviceLineIbtLinkSQLMapper::doMapShuttleOrders()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMapShuttleOrders()");

	// TODO: check ResultSet
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setIbtBranchNo(m_ResultSet.getInt16("ibtbranchno"));
    setIbtCustomerNo(m_ResultSet.getInt32("ibtcustomerno"));
    setIbtCscOrderNo(m_ResultSet.getInt32("ibtorderno"));
    setIbtCscOrderPosNo(m_ResultSet.getInt32("ibtorderposno"));
    setIbtDeliveryAdviceDate(m_ResultSet.getInt32("ibtpositioncreation"));
    setBranchNo(m_ResultSet.getInt16("filialnr"));
    setCustomerNo(m_ResultSet.getInt32("idfnr"));
    setCscOrderNo(m_ResultSet.getInt32("kdauftragnr"));
    setCscOrderPosNo(m_ResultSet.getInt32("posnr"));
}

void DeliveryAdviceLineIbtLinkSQLMapper::doMapShuttleOrderDetails()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineIbtLinkSQLMapper::doMapShuttleOrderDetails()");
	
	// TODO: check ResultSet
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setIbtDeliveryAdviceDate(m_ResultSet.getInt32("rechnungsdatum"));
	basar::VarString deliveryAdviceNo;
	deliveryAdviceNo.itos(m_ResultSet.getInt32("rechnungnr")); // TODO rechnungsnummer lesen aus orderremarks??? Führende Nullen???
    setIbtDeliveryAdviceNo(deliveryAdviceNo);
}

//void DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4ShuttleOrder()
//{
//    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
//        "DeliveryAdviceLineIbtLinkSQLMapper::doMapDeliveryAdvice4ShuttleOrder()");
//
//    // TODO: check ResultSet
//    if (m_ResultSet.isNull())
//    {
//        throw;
//    }
//
//    setIbtDeliveryAdvicePosNo(m_ResultSet.getInt32("ibtdeliveryadviceposno"));
//}

} // end namespace document
} // end namespace libcsc
