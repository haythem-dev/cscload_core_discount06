#include <libbasarcmnutil_bstring.h>
#include "logger/loggerpool.h"
#include "cscorderpossplittinfoinsertsqlparameterbinder.h"
#include "cscorderpossplittinfosqlmapper.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

CSCOrderposSplittinfoSqlMapper::CSCOrderposSplittinfoSqlMapper(
    domMod::CSCOrderposSplittinfoPtr splittinfo, basar::db::sql::ResultsetRef const resultSet)
    : CSCOrderposSplittinfoMapperBase(splittinfo), m_ResultSet(resultSet)
{
}

CSCOrderposSplittinfoSqlMapper::~CSCOrderposSplittinfoSqlMapper()
{
}

void CSCOrderposSplittinfoSqlMapper::doMap()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setCscOrderNo(m_ResultSet.getInt32("cscorderno"));
    setCscOrderPosNo(m_ResultSet.getInt32("cscorderposno"));
    setSplittType(static_cast<SplittTypeEnum>(m_ResultSet.getInt16("splitttype")));
    setOriginal(static_cast<SplittOriginTypeEnum>(m_ResultSet.getInt16("original")));
    setOrderNo(m_ResultSet.getInt32("orderno"));
    setOrderPosNo(m_ResultSet.getInt32("posno"));
}

const basar::VarString CSCOrderposSplittinfoSqlMapper::getSelectSQL(const basar::Int32 cscorderno,
    const basar::Int32 cscorderposno, const basar::Int16 splitttype)
{
    static std::string s1 = "select cscorderno, cscorderposno, splitttype, original, orderno, posno "
                            "from cscorderpossplittinfo where cscorderno = ";
    static std::string s2 = " and cscorderposno = ";
    static std::string s3 = " and splitttype = ";

    std::stringstream ss;
    ss << s1 << cscorderno << s2 << cscorderposno << s3 << splitttype;

    return ss.str();
}

const basar::VarString CSCOrderposSplittinfoSqlMapper::getSelectArchiveSQL(const basar::Int32 cscorderno,
    const basar::Int32 cscorderposno, const basar::Int16 splitttype, const basar::Int32 date)
{
    static std::string s1 = "select cscorderno, cscorderposno, splitttype, original, orderno, posno "
        "from acscorderpossplittinfo where cscorderno = ";
    static std::string s2 = " and cscorderposno = ";
    static std::string s3 = " and splitttype = ";
    static std::string s4 = " and datum = ";

    std::stringstream ss;
    ss << s1 << cscorderno << s2 << cscorderposno << s3 << splitttype << s3 << date;

    return ss.str();
}

basar::VarString const CSCOrderposSplittinfoSqlMapper::getInsertSQL()
{
    static std::string s =  "insert into cscorderpossplittinfo "
                            "(cscorderno, cscorderposno, splitttype, original, orderno, posno) "
                            "values (?, ?, ?, ?, ?, ?)";

    return s;
}

persistence::ISqlParameterBinderPtr const CSCOrderposSplittinfoSqlMapper::getInsertSqlParameterBinder(
    domMod::ICSCOrderposSplittinfoPtr splittinfo)
{
    return persistence::ISqlParameterBinderPtr(new CSCOrderposSplittinfoInsertSqlParameterBinder(splittinfo));
}

void CSCOrderposSplittinfoSqlMapper::bindInsertSQL(
    basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderposSplittinfoPtr splittinfo)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrderPos(), "CSCOrderposSplittinfoSqlMapper::bindInsertSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream tmp;
    tmp << "CSCOrderposSplittinfoSqlMapper::bindInsertSQL("
        << splittinfo->getCscOrderNo() << ", "
        << splittinfo->getCscOrderPosNo() << ", "
        << splittinfo->getSplittType() << ", "
        << splittinfo->getOriginal() << ", "
        << splittinfo->getOrderNo() << ", "
        << splittinfo->getOrderPosNo() << ")";
    BLOG_TRACE(LoggerPool::getLoggerOrderPos(), tmp.str());

    static BindedValues bv;
    bv = setBindedValues(splittinfo);

    basar::UInt32 counter = 0;
    prepStmt.setInt32(counter++, bv.cscOrderNo);
    prepStmt.setInt32(counter++, bv.cscOrderPosNo);
    prepStmt.setInt16(counter++, bv.splittType);
    prepStmt.setInt16(counter++, bv.original);
    prepStmt.setInt32(counter++, bv.orderNo);
    prepStmt.setInt32(counter++, bv.orderPosNo);
}

CSCOrderposSplittinfoSqlMapper::BindedValues CSCOrderposSplittinfoSqlMapper::setBindedValues(domMod::ICSCOrderposSplittinfoPtr splittinfo)
{
    std::stringstream tmp;
    tmp << "CSCOrderposSplittinfoSqlMapper::bindInsertSQL("
        << splittinfo->getCscOrderNo() << ", "
        << splittinfo->getCscOrderPosNo() << ", "
        << splittinfo->getSplittType() << ", "
        << splittinfo->getOriginal() << ", "
        << splittinfo->getOrderNo() << ", "
        << splittinfo->getOrderPosNo() << ")" << std::endl;

    BindedValues bv;
    bv.cscOrderNo = splittinfo->getCscOrderNo();
    bv.cscOrderPosNo = splittinfo->getCscOrderPosNo();
    bv.splittType = static_cast<basar::Int16>(splittinfo->getSplittType());
    bv.original = static_cast<basar::Int16>(splittinfo->getOriginal());
    bv.orderNo = splittinfo->getOrderNo();
    bv.orderPosNo = splittinfo->getOrderPosNo();

    tmp << "binded values: "
        << bv.cscOrderNo << ", "
        << bv.cscOrderPosNo << ", "
        << bv.splittType << ", "
        << bv.original << ", "
        << bv.orderNo << ", "
        << bv.orderPosNo;
    BLOG_TRACE(LoggerPool::getLoggerOrderPos(), tmp.str());
    return bv;
}

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc
