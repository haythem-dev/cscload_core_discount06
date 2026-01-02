#include "csccallplansqlmapper.h"
#include "csccallplaninsertsqlparameterbinder.h"
#include "csccallplanupdatesqlparameterbinder.h"
#include "csccallplanselectsqlparameterbinder.h"
#include "cscorder/csccallplan/csccallplan.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCCallplanSqlMapper::CSCCallplanSqlMapper(domMod::ICSCCallplanPtr cscCallplan, basar::db::sql::ResultsetRef const resultSet)
    : CSCCallplanMapperBase(cscCallplan), m_ResultSet(resultSet)
{
}

CSCCallplanSqlMapper::~CSCCallplanSqlMapper()
{
}

void CSCCallplanSqlMapper::doMap()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setCallTime(m_ResultSet.getInt32("rufzeit"));
    setAction(m_ResultSet.getInt16("lfdaktion"));
}

const basar::VarString CSCCallplanSqlMapper::getSelectSQL()
{
    static std::string s =
        "SELECT tp.lfdaktion, tp.rufzeit "
        "FROM tagplan tp "
        "INNER JOIN tagplanereignis tpe ON"
        "      tpe.idfnr = tp.idfnr"
        "  AND tpe.filialnr = tp.filialnr"
        "  AND tpe.rufzeit = tp.rufzeit"
        "  AND tpe.datum = tp.datum"
        "  AND tpe.lfdaktion = tp.lfdaktion "
        "WHERE "
        "      tp.zugriff = 0"
        "  AND tp.anrufart = 'PH'"
        "  AND (tpe.status = 6 OR tpe.status = 7)"
        "  AND tp.filialnr = ?"
        "  AND tp.idfnr = ?"
        "  AND tp.datum = ?"
        "  AND tpe.rufzeitgeaendert >= ?"
        "  AND tpe.rufzeitgeaendert <= ? "
        "ORDER BY tpe.rufzeitgeaendert, tpe.rufzeit, tp.prioritaet";

    return s.c_str();
}

basar::VarString const CSCCallplanSqlMapper::getInsertSQL()
{
    static std::string s =
        "INSERT INTO tagplanereignis "
        "(filialnr, idfnr, datum, rufzeit, rufzeitgeaendert, lfdaktion, zeit, status, loeschgrund, uid, bemerkung) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, 3, 0, 0, 'Order received')";

    return s.c_str();
}

basar::VarString const CSCCallplanSqlMapper::getUpdateSQL()
{
    static std::string s =
        "UPDATE tagplan "
        "SET lfdaktion = ?, prioritaet = '0' "
        "WHERE filialnr = ?"
        "  AND idfnr = ?"
        "  AND datum = ?"
        "  AND rufzeit = ?";

    return s.c_str();
}

persistence::ISqlParameterBinderPtr const CSCCallplanSqlMapper::getInsertSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan)
{
    return persistence::ISqlParameterBinderPtr(new CSCCallplanInsertSqlParameterBinder(cscCallplan));
}

persistence::ISqlParameterBinderPtr const CSCCallplanSqlMapper::getUpdateSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan)
{
    return persistence::ISqlParameterBinderPtr(new CSCCallplanUpdateSqlParameterBinder(cscCallplan));
}

persistence::ISqlParameterBinderPtr const CSCCallplanSqlMapper::getSelectSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan)
{
    return persistence::ISqlParameterBinderPtr(new CSCCallplanSelectSqlParameterBinder(cscCallplan));
}

void CSCCallplanSqlMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCCallplanPtr cscCallplan)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCCallplanSqlMapper::bindInsertSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream log;
    log << "CSCCallplanSqlMapper::bindInsertSQL( BranchNo: " << cscCallplan->getBranchNo()
        << ", CustomerNo: " << cscCallplan->getCustomerNo() << ", Date: " << cscCallplan->getDate() << ", CallTime: " << cscCallplan->getCallTime()
        << ", Action: " << cscCallplan->getAction() << ", TimeNow: " << cscCallplan->getTimeNow() << " )";
    BLOG_TRACE(LoggerPool::getLoggerOrder(), log.str());

    static BindedValues bv;
    bv = setBindedValues(cscCallplan);

    basar::UInt32 counter = 0;
    prepStmt.setInt16(counter++, bv.branchNo);
    prepStmt.setInt32(counter++, bv.customerNo);
    prepStmt.setInt32(counter++, bv.date);
    prepStmt.setInt32(counter++, bv.callTime);
    prepStmt.setInt32(counter++, bv.callTime);
    prepStmt.setInt16(counter++, bv.action);
    prepStmt.setInt32(counter++, bv.timeNow);
}

void CSCCallplanSqlMapper::bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCCallplanPtr cscCallplan)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCCallplanSqlMapper::bindUpdateSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream log;
    log << "CSCCallplanSqlMapper::bindUpdateSQL( BranchNo: " << cscCallplan->getBranchNo()
        << ", CustomerNo: " << cscCallplan->getCustomerNo() << ", CallTime: " << cscCallplan->getCallTime()
        << ", Action: " << cscCallplan->getAction() << ", Date: " << cscCallplan->getDate() << " )";
    BLOG_TRACE(LoggerPool::getLoggerOrder(), log.str());

    static BindedValues bv;
    bv = setBindedValues(cscCallplan);

    basar::UInt32 counter = 0;
    prepStmt.setInt16(counter++, bv.action);
    prepStmt.setInt16(counter++, bv.branchNo);
    prepStmt.setInt32(counter++, bv.customerNo);
    prepStmt.setInt32(counter++, bv.date);
    prepStmt.setInt32(counter++, bv.callTime);
}

void CSCCallplanSqlMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCCallplanPtr cscCallplan)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCCallplanSqlMapper::bindSelectSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream log;
    log << "CSCCallplanSqlMapper::bindSelectSQL( BranchNo: " << cscCallplan->getBranchNo()
        << ", CustomerNo: " << cscCallplan->getCustomerNo() << ", TimeNow: " << cscCallplan->getTimeNow() 
        << ", TimeFrom: " << cscCallplan->getTimeFrom() << ", TimeTo: " << cscCallplan->getTimeTo() << " )";
    BLOG_TRACE(LoggerPool::getLoggerOrder(), log.str());

    static BindedValues bv;
    bv = setBindedValues(cscCallplan);

    basar::UInt32 counter = 0;
    prepStmt.setInt16(counter++, bv.branchNo);
    prepStmt.setInt32(counter++, bv.customerNo);
    prepStmt.setInt32(counter++, bv.date);
    prepStmt.setInt32(counter++, bv.timeFrom);
    prepStmt.setInt32(counter++, bv.timeTo);
}

CSCCallplanSqlMapper::BindedValues CSCCallplanSqlMapper::setBindedValues(domMod::ICSCCallplanPtr cscCallplan)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCCallplanSqlMapper::setBindedValues()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream log;
    log << "CSCCallplanSqlMapper::setBindedValues( BranchNo: " << cscCallplan->getBranchNo()
        << ", CustomerNo: " << cscCallplan->getCustomerNo() << ", CallTime: " << cscCallplan->getCallTime()
        << ", Date: " << cscCallplan->getDate()
        << ", Action: " << cscCallplan->getAction() << ", TimeNow: " << cscCallplan->getTimeNow()
        << ", TimeFrom: " << cscCallplan->getTimeFrom() << ", TimeTo: " << cscCallplan->getTimeTo() << " )";

    BindedValues bv;
    bv.branchNo = cscCallplan->getBranchNo();
    bv.customerNo = cscCallplan->getCustomerNo();
    bv.date = cscCallplan->getDate();
    bv.timeNow = cscCallplan->getTimeNow();
    bv.timeFrom = cscCallplan->getTimeFrom();
    bv.timeTo = cscCallplan->getTimeTo();
    bv.callTime = cscCallplan->getCallTime();
    bv.action = cscCallplan->getAction();

    BLOG_TRACE(LoggerPool::getLoggerOrder(), log.str());
    return bv;
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
