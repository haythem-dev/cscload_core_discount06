#include "cscorderflagssqlmapper.h"
#include "cscorder/cscorderflags/cscorderflags.h"

#include "cscorderflagsinsertsqlparameterbinder.h"
#include "cscorderflagsupdatesqlparameterbinder.h"

#include "logger/loggerpool.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace cscorder {
namespace repo {

// ------------------------------------------------------------------------------------------------------------------------------------------------------
CSCOrderFlagsSqlMapper::CSCOrderFlagsSqlMapper(domMod::CSCOrderFlagsPtr cscOrderFlags, basar::db::sql::ResultsetRef const resultSet)
    : CSCOrderFlagsMapperBase(cscOrderFlags), m_ResultSet(resultSet)
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
CSCOrderFlagsSqlMapper::~CSCOrderFlagsSqlMapper()
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlagsSqlMapper::doMap()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setCscOrderNo(m_ResultSet.getInt32("cscorderno"));
    setNoDelayedDelivery(basar::Int16(1) == m_ResultSet.getInt16("nodelayeddelivery"));
    setWaitForIbtPicking(basar::Int16(1) == m_ResultSet.getInt16("waitforibtpicking"));
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
bool CSCOrderFlagsSqlMapper::isInsertable(domMod::ICSCOrderFlagsPtr cscOrderFlags)
{
    return cscOrderFlags->getCscOrderNo().isDirty(); // Key Value!!!
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
bool CSCOrderFlagsSqlMapper::isUpdatable(domMod::ICSCOrderFlagsPtr cscOrderFlags)
{    
    return cscOrderFlags->getCscOrderNo().isClean(); // Key Value!!!
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
const basar::VarString CSCOrderFlagsSqlMapper::getSelectSQL( const basar::Int32 cscorderno )
{
    static std::string s1 = "select cscorderno"
                            ", nodelayeddelivery "
                            ", waitforibtpicking "
                            "from cscorderflags where cscorderno = ";

    std::stringstream ss;
    ss << s1 << cscorderno;

    return ss.str().c_str();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
basar::VarString const CSCOrderFlagsSqlMapper::getInsertSQL()
{
    static std::string s =  "INSERT INTO cscorderflags "
                            "(cscorderno, nodelayeddelivery, waitforibtpicking) "
                            "VALUES (?, ?, ?)";

    return s.c_str();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
basar::VarString const CSCOrderFlagsSqlMapper::getUpdateSQL()
{
    static std::string s =  "UPDATE cscorderflags "
                            "SET nodelayeddelivery = ?, waitforibtpicking = ? "
                            "WHERE cscorderno = ?";

    return s.c_str();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
basar::VarString const CSCOrderFlagsSqlMapper::getDeleteSQL(const basar::Int32 cscorderno)
{
    static std::string s = "DELETE FROM cscorderflags WHERE cscorderno = ";

    std::stringstream ss;
    ss << s << cscorderno;

    return ss.str().c_str();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
persistence::ISqlParameterBinderPtr const CSCOrderFlagsSqlMapper::getInsertSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags)
{
    return persistence::ISqlParameterBinderPtr(new CSCOrderFlagsInsertSqlParameterBinder(cscOrderFlags));
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
persistence::ISqlParameterBinderPtr const CSCOrderFlagsSqlMapper::getUpdateSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags)
{
    return persistence::ISqlParameterBinderPtr(new CSCOrderFlagsUpdateSqlParameterBinder(cscOrderFlags));
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlagsSqlMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderFlagsPtr cscOrderFlags)
{		
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCOrderFlagsSqlMapper::bindInsertSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream tmp;
    tmp << "CSCOrderFlagsSqlMapper::bindInsertSQL (OrderNo " << cscOrderFlags->getCscOrderNo()
        << ", NoDelayedDelivery " << cscOrderFlags->isNoDelayedDelivery()
        << ", WaitForIbtPicking " << cscOrderFlags->isWaitForIbtPicking() << " ) ";
    BLOG_TRACE(LoggerPool::getLoggerOrder(), tmp.str().c_str());

    static BindedValues bv;
    bv = setBindedValues(cscOrderFlags);

    basar::UInt32 counter = 0;
    prepStmt.setInt32(counter++, bv.cscOrderNo);
    prepStmt.setInt16(counter++, bv.noDelayedDelivery);
    prepStmt.setInt16(counter++, bv.waitForIbtPicking);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
CSCOrderFlagsSqlMapper::BindedValues CSCOrderFlagsSqlMapper::setBindedValues(domMod::ICSCOrderFlagsPtr cscOrderFlags)
{
    std::stringstream tmp;
    tmp << "CSCOrderFlagsSqlMapper::setBindedValues (OrderNo " << cscOrderFlags->getCscOrderNo()
        << ", NoDelayedDelivery " << cscOrderFlags->isNoDelayedDelivery()
        << ", WaitForIbtPicking " << cscOrderFlags->isWaitForIbtPicking() << " ): ";

    BindedValues bv;
    bv.cscOrderNo = cscOrderFlags->getCscOrderNo();
    bv.noDelayedDelivery = cscOrderFlags->isNoDelayedDelivery() ? basar::Int16(1) : basar::Int16(0);
    bv.waitForIbtPicking = cscOrderFlags->isWaitForIbtPicking() ? basar::Int16(1) : basar::Int16(0);

    tmp << "binded values: cscOrderNo " << bv.cscOrderNo
        << " noDelayedDelivery " << bv.noDelayedDelivery << " waitForIbtPicking " << bv.waitForIbtPicking;
    BLOG_TRACE(LoggerPool::getLoggerOrder(), tmp.str().c_str());
    return bv;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlagsSqlMapper::bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderFlagsPtr cscOrderFlags)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCOrderFlagsSqlMapper::bindUpdateSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream tmp;
    tmp << "CSCOrderFlagsSqlMapper::bindUpdateSQL (OrderNo " << cscOrderFlags->getCscOrderNo()
        << ", NoDelayedDelivery " << cscOrderFlags->isNoDelayedDelivery()
        << ", WaitForIbtPicking " << cscOrderFlags->isWaitForIbtPicking() << " ) ";
    BLOG_TRACE(LoggerPool::getLoggerOrder(), tmp.str().c_str());

    static BindedValues bv;
    bv = setBindedValues(cscOrderFlags);

    basar::UInt32 counter = 0;
    prepStmt.setInt16(counter++, bv.noDelayedDelivery);
    prepStmt.setInt16(counter++, bv.waitForIbtPicking);
    prepStmt.setInt32(counter++, bv.cscOrderNo);
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
