#include <libbasarcmnutil_bstring.h>
#include "logger/loggerpool.h"
#include "cscorderibtpickingdatainsertsqlparameterbinder.h"
#include "cscorderibtpickingdatasqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderIBTPickingdataSqlMapper::CSCOrderIBTPickingdataSqlMapper(
    domMod::CSCOrderIBTPickingdataPtr pickingdata, basar::db::sql::ResultsetRef const resultSet)
    : CSCOrderIBTPickingdataMapperBase(pickingdata), m_ResultSet(resultSet)
{
}

CSCOrderIBTPickingdataSqlMapper::~CSCOrderIBTPickingdataSqlMapper()
{
}

void CSCOrderIBTPickingdataSqlMapper::doMap()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setCscOrderNo(m_ResultSet.getInt32("cscorderno"));
    setCscOrderPosNo(m_ResultSet.getInt32("cscorderposno"));
    setDeliveryPosNo(m_ResultSet.getInt32("deliveryposno"));
    setQuantity(m_ResultSet.getInt32("quantity"));
    setBatch(m_ResultSet.getString("batch"));
    setExpiryDate(m_ResultSet.getInt32("expirydate"));
}

const basar::VarString CSCOrderIBTPickingdataSqlMapper::getSelectSQL(
    const basar::Int32 cscorderno, const basar::Int32 cscorderposno)
{
    static std::string s1 = "select cscorderno, cscorderposno, deliveryposno, quantity, batch, expirydate "
                            "from cscorderibtpickingdata where cscorderno = ";
    static std::string s2 = " and cscorderposno = ";

    std::stringstream ss;
    ss << s1 << cscorderno << s2 << cscorderposno;

    return ss.str();
}

basar::VarString const CSCOrderIBTPickingdataSqlMapper::getInsertSQL()
{
    static std::string s =  "insert into cscorderibtpickingdata "
                            "(cscorderno, cscorderposno, deliveryposno, quantity, batch, expirydate) "
                            "values (?, ?, ?, ?, ?, ?)";

    return s;
}

persistence::ISqlParameterBinderPtr const CSCOrderIBTPickingdataSqlMapper::getInsertSqlParameterBinder(
    domMod::ICSCOrderIBTPickingdataPtr pickingdata)
{
    return persistence::ISqlParameterBinderPtr(new CSCOrderIBTPickingdataInsertSqlParameterBinder(pickingdata));
}

void CSCOrderIBTPickingdataSqlMapper::bindInsertSQL(
    basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderIBTPickingdataPtr pickingdata)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerIbtRequest(), "CSCOrderIBTPickingdataSqlMapper::bindInsertSQL()");

    // Prepared statement setters take a reference and only move the address to the client sdk layer.
    // We have to take sure, variables are still existent at that moment execute() ist called!

    std::stringstream tmp;
    tmp << "CSCOrderIBTPickingdataSqlMapper::bindInsertSQL("
        << pickingdata->getCscOrderNo() << ", "
        << pickingdata->getCscOrderPosNo() << ", "
        << pickingdata->getDeliveryPosNo() << ", "
        << pickingdata->getQuantity() << ", "
        << pickingdata->getBatch() << ", "
        << pickingdata->getExpiryDate() << ")";
    BLOG_TRACE(LoggerPool::getLoggerIbtRequest(), tmp.str());

    static BindedValues bv;
    bv = setBindedValues(pickingdata);
    
    basar::UInt32 counter = 0;
    prepStmt.setInt32(counter++, bv.cscOrderNo);
    prepStmt.setInt32(counter++, bv.cscOrderPosNo);
    prepStmt.setInt32(counter++, bv.deliveryPosNo);
    prepStmt.setInt32(counter++, bv.quantity);
    prepStmt.setString(counter++, bv.batch.c_str());
    prepStmt.setInt32(counter++, bv.expiryDate);
}

CSCOrderIBTPickingdataSqlMapper::BindedValues CSCOrderIBTPickingdataSqlMapper::setBindedValues(
    domMod::ICSCOrderIBTPickingdataPtr pickingdata)
{
    std::stringstream tmp;
    tmp << "CSCOrderIBTPickingdataSqlMapper::bindInsertSQL("
        << pickingdata->getCscOrderNo() << ", "
        << pickingdata->getCscOrderPosNo() << ", "
        << pickingdata->getDeliveryPosNo() << ", "
        << pickingdata->getQuantity() << ", "
        << pickingdata->getBatch() << ", "
        << pickingdata->getExpiryDate() << ")" << std::endl;

    BindedValues bv;
    bv.cscOrderNo = pickingdata->getCscOrderNo();
    bv.cscOrderPosNo = pickingdata->getCscOrderPosNo();
    bv.deliveryPosNo = pickingdata->getDeliveryPosNo();
    bv.quantity = pickingdata->getQuantity();
    bv.batch = pickingdata->getBatch();
    bv.expiryDate = pickingdata->getExpiryDate();

    tmp << "binded values: "
        << bv.cscOrderNo << ", "
        << bv.cscOrderPosNo << ", "
        << bv.deliveryPosNo << ", "
        << bv.quantity << ", "
        << bv.batch << ", "
        << bv.expiryDate;
    BLOG_TRACE(LoggerPool::getLoggerIbtRequest(), tmp.str());
    return bv;
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
