#include <customer/tenderinfo/tenderinfosqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace customer {

TenderInfoSqlMapper::TenderInfoSqlMapper(TenderInfoPtr tenderInfo, const basar::db::sql::ResultsetRef resultSet) :
    TenderInfoMapperBase(tenderInfo),
    m_ResultSet(resultSet)
{
}

TenderInfoSqlMapper::~TenderInfoSqlMapper()
{
}

const basar::VarString TenderInfoSqlMapper::getSelectSQL(const basar::Int16 branchNo,
    const basar::Int32 customerNo, const basar::VarString& /*contractNo*/, const basar::Int32 articleNo)
{
    basar::Date now = basar::Date::getCurrent();
    std::stringstream sql;
    sql << "SELECT "
                "k.vertriebszentrumnr AS branchno, "
                "k.idfnr AS customerno, "
                "th.tenderno AS tenderno, "
                "th.contractno AS contractno, "
                "th.datefrom AS validfromdate, "
                "th.dateto AS validtodate, "
                "th.pharmacychainno AS pharmacychainno,"
                "tp.articleno AS articleno, "
                "tp.contractqty AS tenderquantity, "
                "CAST(sum(NVL(tpr.deliveryqty, 0)) AS INTEGER) AS deliveredtenderquantity, "
                "CAST(sum(NVL(tpr.returnqty, 0)) AS INTEGER) AS returnedtenderquantity "
            "FROM kunde k "
                "JOIN tenderhead th ON (k.vertriebszentrumnr = th.branchno AND k.idfnr = th.customerno AND th.customerno > 0) OR "
                    "(k.mastercstno = th.pharmacychainno AND th.pharmacychainno > 0) "
                "JOIN tenderpos tp ON tp.tenderno = th.tenderno "
                "LEFT OUTER JOIN tenderprogress tpr ON tpr.tenderno = tp.tenderno and tpr.articleno = tp.articleno "
            "WHERE k.vertriebszentrumnr = " << branchNo << " AND "
                "(th.datefrom < " << now.getDate() << " AND th.dateto > " << now.getDate() << ") ";
    if (customerNo > 0)
    {
        sql <<  "AND k.idfnr = " << customerNo << " ";
    }
    if (articleNo > 0)
    {
        sql << "AND tp.articleno = " << articleNo << " ";
    }
    //  and tp.contractqty>0 and th.pharmacychainno>0
    sql <<  "GROUP BY 1, 2, 3, 4, 5, 6, 7, 8, 9 "
            "ORDER BY 1, 2, 3, 8";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}

void TenderInfoSqlMapper::doMap()
{
    if( m_ResultSet.isNull() )
    {
        throw;
    }

    setBranchNo                 (m_ResultSet.getInt16("branchno"));
    setCustomerNo               (m_ResultSet.getInt32("customerno"));
    setTenderNo                 (m_ResultSet.getInt32("tenderno"));
    setContractNo               (m_ResultSet.getString("contractno"));
    setValidFromDate            (m_ResultSet.getInt32("validfromdate"));
    setValidToDate              (m_ResultSet.getInt32("validtodate"));
    setChainNo                  (m_ResultSet.getInt32("pharmacychainno"));

    setArticleNo                (m_ResultSet.getInt32("articleno"));
    setTenderQuantity           (m_ResultSet.getInt32("tenderquantity"));
//  setFreeTenderQuantity       (m_ResultSet.getInt32("freetenderquantity"));
    setDeliveredTenderQuantity  (m_ResultSet.getInt32("deliveredtenderquantity"));
    setReturnedTenderQuantity   (m_ResultSet.getInt32("returnedtenderquantity"));
}


} // end namespace customer
} // end namespace libcsc

