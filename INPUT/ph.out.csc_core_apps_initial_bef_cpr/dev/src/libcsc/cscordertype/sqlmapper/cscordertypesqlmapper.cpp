#include "cscordertypesqlmapper.h"
#include <cscordertype/cscordertype.h>
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace cscordertype
{
CSCOrderTypeSqlMapper::CSCOrderTypeSqlMapper( 
    CSCOrderTypePtr orderType, 
    const basar::db::sql::ResultsetRef resultSet 
    )
: CSCOrderTypeMapperBase( orderType ),
  m_ResultSet( resultSet )
{
}

CSCOrderTypeSqlMapper::~CSCOrderTypeSqlMapper()
{
}

bool CSCOrderTypeSqlMapper::isInsertable( const CSCOrderTypePtr orderType )
{
	return ( orderType->getBranchNo().isDirty() && orderType->getOrderType().isDirty() );
}

bool CSCOrderTypeSqlMapper::isUpdatable( const CSCOrderTypePtr orderType )
{
	return ( orderType->getBranchNo().isClean() && orderType->getOrderType().isClean() && orderType->containsDirty() );
}

bool CSCOrderTypeSqlMapper::isDeletable( const CSCOrderTypePtr orderType )
{
	return ( orderType->getBranchNo().isClean() && orderType->getOrderType().isClean() );
}

const basar::VarString CSCOrderTypeSqlMapper::getMultiSelectSQL( const basar::Int16 branchNo )
{
	// TODO: Test
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "CSCOrderTypeSqlMapper::getMultiSelectSQL()");

	std::stringstream sql;
	sql << "SELECT "
		"branchno, "
		"kdauftragart, "
		"bezeichnung, "
		"skdauftragartnatra, "
		"skdauftragartnetto, "
		"sglobal, "
		"sbildschirm, "
		"sdafue, "
		"sstandard, "
		"disinkindenterable, "
		"sdiscountable, "
		"smustsuborder, "
		"sfreeprice, "
		"sordercons, "
		"srestdel, "
		"snoquota, "
		"snopartqty, "
		"sdeferorder, "
		"snodd, "
		"sonlyeh, "
		"snopromotions, "
		"sdefaultkennung, "
		"sivcvoucherno, "
		"soriginalinvoiceno, "
		"stockreservation "
		"FROM kdauftragart WHERE branchno = " << branchNo << " ORDER BY kdauftragart ";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str().c_str());

    return sql.str().c_str();
}

const basar::VarString CSCOrderTypeSqlMapper::getSingleSelectSQL( const basar::Int16 branchNo, const basar::VarString & orderType )
{
	// TODO: Test
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "CSCOrderTypeSqlMapper::getSingleSelectSQL()");

	std::stringstream sql;
    sql << "SELECT "
		"branchno, "
		"kdauftragart, "
		"bezeichnung, "
		"skdauftragartnatra, "
		"skdauftragartnetto, "
		"sglobal, "
		"sbildschirm, "
		"sdafue, "
		"sstandard, "
		"disinkindenterable, "
		"sdiscountable, "
		"smustsuborder, "
		"sfreeprice, "
		"sordercons, "
		"srestdel, "
		"snoquota, "
		"snopartqty, "
		"sdeferorder, "
		"snodd, "
		"sonlyeh, "
		"snopromotions, "
		"sdefaultkennung, "
		"sivcvoucherno, "
		"soriginalinvoiceno, "
		"stockreservation "
		"FROM kdauftragart WHERE branchno = " << branchNo << " AND kdauftragart = '" << orderType << "'";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str().c_str());

    return sql.str().c_str();
}

const basar::VarString CSCOrderTypeSqlMapper::getInsertSQL( const CSCOrderTypePtr orderType )
{
	// TODO
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "CSCOrderTypeSqlMapper::getInsertSQL()");

	std::stringstream sql;
    sql << "INSERT INTO kdauftragart" << 
		"( "
		"branchno, "
		"kdauftragart, "
		"bezeichnung, "
		"skdauftragartnatra, "
		"skdauftragartnetto, "
		"sglobal, "
		"sbildschirm, "
		"sdafue, "
		"sstandard, "
		"disinkindenterable, "
		"sdiscountable, "
		"smustsuborder, "
		"sfreeprice, "
		"sordercons, "
		"srestdel, "
		"snoquota, "
		"snopartqty, "
		"sdeferorder, "
		"snodd, "
		"sonlyeh, "
		"snopromotions, "
		"sdefaultkennung, "
		"sivcvoucherno, "
		"soriginalinvoiceno, "
		"stockreservation "
		") VALUES ( "
		<< orderType->getBranchNo().get()
		<< ", '" << orderType->getOrderType().c_str()
		<< "', '" << orderType->getDescription().c_str()
		<< "','" << (orderType->getNatra() ? "1" : "0")
		<< "','" << (orderType->getNetto() ? "1" : "0")
		<< "','" << (orderType->getGlobal() ? "1" : "0")
		<< "','" << (orderType->getBild() ? "1" : "0")
		<< "','" << (orderType->getDafue() ? "1" : "0")
		<< "','" << (orderType->getStandard() ? "1" : "0")
		<< "','" << (orderType->getHand() ? "1" : "0")
		<< "','" << (orderType->getDiscount() ? "1" : "0")
		<< "','" << (orderType->getMuss() ? "1" : "0")
		<< "','" << (orderType->getFreePrice() ? "1" : "0")
		<< "','" << (orderType->getAufCons() ? "1" : "0")
		<< "','" << (orderType->getAufNachl() ? "1" : "0")
		<< "','" << (orderType->getNoQuota() ? "1" : "0")
		<< "','" << (orderType->getNoPart() ? "1" : "0")
		<< "','" << (orderType->getDeferOrder() ? "1" : "0")
		<< "','" << (orderType->getNoDD() ? "1" : "0")
		<< "','" << (orderType->getOnlyEH() ? "1" : "0")
		<< "'," << (orderType->getNoPromo() ? "1" : "0")
		<< "," << (orderType->getDefaultKennung() ? "1" : "0")
		<< "," << (orderType->getIVC() ? "1" : "0")
		<< "," << (orderType->getOrgInvoice() ? "1" : "0")
		<< "," << (orderType->getStockreservation() ? "1" : "0")
		<< ") ";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str().c_str());

    return sql.str().c_str();
}

const basar::VarString CSCOrderTypeSqlMapper::getUpdateSQL( const CSCOrderTypePtr orderType )
{
	// TODO
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "CSCOrderTypeSqlMapper::getUpdateSQL()");

	std::stringstream sql;

	sql << "UPDATE kdauftragart set "
		"bezeichnung = '" << orderType->getDescription().c_str() <<
		"',skdauftragartnatra = '" << (orderType->getNatra() ? "1" : "0") <<
		"',skdauftragartnetto = '" << (orderType->getNetto() ? "1" : "0") <<
		"',sglobal = '" << (orderType->getGlobal() ? "1" : "0") <<
		"',sbildschirm = '" << (orderType->getBild() ? "1" : "0") <<
		"',sdafue = '" << (orderType->getDafue() ? "1" : "0") <<
		"',sstandard = '" << (orderType->getStandard() ? "1" : "0") <<
		"',disinkindenterable = '" << (orderType->getHand() ? "1" : "0") <<
		"',sdiscountable = '" << (orderType->getDiscount() ? "1" : "0") <<
		"',smustsuborder = '" << (orderType->getMuss() ? "1" : "0") <<
		"',sfreeprice = '" << (orderType->getFreePrice() ? "1" : "0") <<
		"',sordercons = '" << (orderType->getAufCons() ? "1" : "0") <<
		"',srestdel = '" << (orderType->getAufNachl() ? "1" : "0") <<
		"',snoquota = '" << (orderType->getNoQuota() ? "1" : "0") <<
		"',snopartqty = '" << (orderType->getNoPart() ? "1" : "0") <<
		"',sdeferorder = '" << (orderType->getDeferOrder() ? "1" : "0") <<
		"',snodd = '" << (orderType->getNoDD() ? "1" : "0") <<
		"',sonlyeh = '" << (orderType->getOnlyEH() ? "1" : "0") <<
		"',snopromotions = " << (orderType->getNoPromo() ? "1" : "0") <<
		",sdefaultkennung = " << (orderType->getDefaultKennung() ? "1" : "0") <<
		",sivcvoucherno = " << (orderType->getIVC() ? "1" : "0") <<
		",soriginalinvoiceno = " << (orderType->getOrgInvoice() ? "1" : "0") <<
		",stockreservation = " << (orderType->getStockreservation() ? "1" : "0") <<
		"WHERE "
		"branchno = " << orderType->getBranchNo().get() <<
		"and kdauftragart = '" << orderType->getOrderType().c_str() <<
		"'"
		;

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str().c_str());

    return sql.str().c_str();
}

const basar::VarString CSCOrderTypeSqlMapper::getDeleteSQL( const CSCOrderTypePtr orderType )
{
	// TODO
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "CSCOrderTypeMapper::getDeleteSQL()");

	std::stringstream sql;
	sql << "DELETE FROM kdauftragart WHERE branchno = " << orderType->getBranchNo().get() << " AND kdauftragart = '" << orderType->getOrderType().c_str() << "'";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str().c_str());

    return sql.str().c_str();
}

void CSCOrderTypeSqlMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	static basar::VarString ValueSet = "1";
	

	setBranchNo( m_ResultSet.getInt16( "branchno" ) );
	setOrderType( m_ResultSet.getString( "kdauftragart" ) ) ;
	setDescription( m_ResultSet.getString( "bezeichnung" ) ) ;
	setGlobal(m_ResultSet.getString("sglobal") == ValueSet);
	setNatra(m_ResultSet.getString("skdauftragartnatra") == ValueSet);
	setNetto(m_ResultSet.getString("skdauftragartnetto") == ValueSet);
	setBild(m_ResultSet.getString("sbildschirm") == ValueSet);
	setHand(m_ResultSet.getString("disinkindenterable") == ValueSet);
	setDafue(m_ResultSet.getString("sdafue") == ValueSet);
	setDiscount(m_ResultSet.getString("sdiscountable") == ValueSet);
	setStandard(m_ResultSet.getString("sstandard") == ValueSet);
	setMuss(m_ResultSet.getString("smustsuborder") == ValueSet);
	setFreePrice(m_ResultSet.getString("sfreeprice") == ValueSet);
	setAufCons(m_ResultSet.getString("sordercons") == ValueSet);
	setAufNachl(m_ResultSet.getString("srestdel") == ValueSet);
	setNoQuota(m_ResultSet.getString("snoquota") == ValueSet);
	setDeferOrder(m_ResultSet.getString("sdeferorder") == ValueSet);
	setNoPart(m_ResultSet.getString("snopartqty") == ValueSet);
	setNoDD(m_ResultSet.getString("snodd") == ValueSet);
	setOnlyEH(m_ResultSet.getString("sonlyeh") == ValueSet);
	setIVC(0 != m_ResultSet.getInt16("sivcvoucherno"));
	setOrgInvoice(0 != m_ResultSet.getInt16("soriginalinvoiceno"));
	setNoPromo(0 != m_ResultSet.getInt16("snopromotions"));
	setDefaultKennung(0 != m_ResultSet.getInt16("sdefaultkennung"));
	setStockreservation(0 != m_ResultSet.getInt16("stockreservation"));
}

} // end namespace cscordertype
} // end namespace libcsc

