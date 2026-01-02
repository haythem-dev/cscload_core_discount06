#include "orderresponsesqlmapper.h"
#include "orderresponse.h"
#include "orderresponseselectsqlparameterbinder.h"
#include "orderresponseinsertsqlparameterbinder.h"
#include "orderresponseupdatesqlparameterbinder.h"

namespace libcsc {
namespace msv3 {

OrderResponseSQLMapper::OrderResponseSQLMapper(OrderResponsePtr orderResponse, const basar::db::sql::ResultsetRef resultSet) :
	OrderResponseMapperBase(orderResponse),
	m_ResultSet(resultSet)
{
}

OrderResponseSQLMapper::OrderResponseSQLMapper(OrderResponsePtr orderResponse) :
	OrderResponseMapperBase(orderResponse)
{
}

OrderResponseSQLMapper::~OrderResponseSQLMapper()
{
}

//----------------------------------------------------------------------------------
// SELECT by transmission UUID
//----------------------------------------------------------------------------------
const basar::VarString OrderResponseSQLMapper::getSelectSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
		"SELECT "
			"id, "
			"orderresponseid, "
			"orderuuid, "
			"orderid, "
			"bundleid, "
			"orderidentifier, "
			"ordersupportid "
		"FROM "
			"orderresponsesuuid "
		"WHERE "
			"orderuuid = ?";
	}
	return sql;
}

void OrderResponseSQLMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::VarString& orderUuid)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::VarString _orderUuid = basar::VarString();

	_orderUuid = orderUuid;

	basar::UInt32 counter = 0;

	prepStmt.setString(counter++, _orderUuid.c_str());
}

const libcsc::persistence::ISqlParameterBinderPtr OrderResponseSQLMapper::getSelectSqlParameterBinder(const basar::VarString& orderUuid)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new OrderResponseSelectSqlParameterBinder(orderUuid));
}


//----------------------------------------------------------------------------------
// INSERT
//----------------------------------------------------------------------------------
const basar::VarString OrderResponseSQLMapper::getInsertSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
		"INSERT INTO orderresponsesuuid "
		"("
			"orderresponseid, "
			"orderuuid, "
			"orderid, "
			"bundleid, "
			"orderidentifier, "
			"ordersupportid "
		") "
		"VALUES "
		"("
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"? "
		")";
	}
	return sql;
}

void OrderResponseSQLMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const OrderResponsePtr orderResponse)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 transmissionId = 0;
	static basar::VarString orderUuid = basar::VarString();
	static basar::Int32 cscOrderNo = 0;
	static basar::VarString bundleId = basar::VarString();
	static basar::VarString orderLabel = basar::VarString();
	static basar::Int32 orderSupportId = 0;

	transmissionId		= orderResponse->getTransmissionId();
	orderUuid			= orderResponse->getOrderUuid();
	cscOrderNo			= orderResponse->getCscOrderNo();
	bundleId			= orderResponse->getBundleId();
	orderLabel			= orderResponse->getOrderLabel();
	orderSupportId		= orderResponse->getOrderSupportId();

	basar::UInt32 counter = 0;

	prepStmt.setInt32	(counter++, transmissionId);
	prepStmt.setString	(counter++, orderUuid.c_str());
	prepStmt.setInt32	(counter++, cscOrderNo);
	prepStmt.setString	(counter++, bundleId.c_str());
	prepStmt.setString	(counter++, orderLabel.c_str());
	prepStmt.setInt32	(counter++, orderSupportId);
}

const libcsc::persistence::ISqlParameterBinderPtr OrderResponseSQLMapper::getInsertSqlParameterBinder(const OrderResponsePtr orderResponse)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new OrderResponseInsertSqlParameterBinder(orderResponse));
}

//----------------------------------------------------------------------------------
// UPDATE
//----------------------------------------------------------------------------------
const basar::VarString OrderResponseSQLMapper::getUpdateSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
		"UPDATE orderresponsesuuid SET "
			"orderresponseid = ?, "
			"orderuuid = ?, "
			"orderid = ?, "
			"bundleid = ?, "
			"orderidentifier = ?, "
			"ordersupportid = ? "
		"WHERE "
			"id = ?";
	}
	return sql;
}

void OrderResponseSQLMapper::bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, const OrderResponsePtr orderResponse)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 transmissionId = 0;
	static basar::VarString orderUuid = basar::VarString();
	static basar::Int32 cscOrderNo = 0;
	static basar::VarString bundleId = basar::VarString();
	static basar::VarString orderLabel = basar::VarString();
	static basar::Int32 orderSupportId = 0;
	static basar::Int32 id = 0;


	transmissionId		= orderResponse->getTransmissionId();
	orderUuid			= orderResponse->getOrderUuid();
	cscOrderNo			= orderResponse->getCscOrderNo();
	bundleId			= orderResponse->getBundleId();
	orderLabel			= orderResponse->getOrderLabel();
	orderSupportId		= orderResponse->getOrderSupportId();
	id					= orderResponse->getId();

	basar::UInt32 counter = 0;

	prepStmt.setInt32	(counter++, transmissionId);
	prepStmt.setString	(counter++, orderUuid.c_str());
	prepStmt.setInt32	(counter++, cscOrderNo);
	prepStmt.setString	(counter++, bundleId.c_str());
	prepStmt.setString	(counter++, orderLabel.c_str());
	prepStmt.setInt32	(counter++, orderSupportId);
	prepStmt.setInt32	(counter++, id);
}

const libcsc::persistence::ISqlParameterBinderPtr OrderResponseSQLMapper::getUpdateSqlParameterBinder(const OrderResponsePtr orderResponse)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new OrderResponseUpdateSqlParameterBinder(orderResponse));
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void OrderResponseSQLMapper::doMap()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setId						(m_ResultSet.getInt32("id"));
	setTransmissionId			(m_ResultSet.getInt32("orderresponseid"));
	setOrderUuid				(m_ResultSet.getString("orderuuid"));
	setCscOrderNo				(m_ResultSet.getInt32("orderid"));
	setBundleId					(m_ResultSet.getString("bundleid"));
	setOrderLabel				(m_ResultSet.getString("orderidentifier"));
	setOrderSupportId			(m_ResultSet.getInt32("ordersupportid"));
}

//----------------------------------------------------------------------------------
// Mapping after insert
//----------------------------------------------------------------------------------
void OrderResponseSQLMapper::doMapSerial(const basar::Int32& id)
{
	setId(id);
	setClean();
}

} // end namespace msv3
} // end namespace libcsc
