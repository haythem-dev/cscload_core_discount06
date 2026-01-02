#include "deliveryadvicesqlmapper.h"
#include "deliveryadvice.h"

namespace libcsc {
namespace document {

DeliveryAdviceSQLMapper::DeliveryAdviceSQLMapper(DeliveryAdvicePtr deliveryAdvice, const basar::db::sql::ResultsetRef resultSet) :
    DeliveryAdviceMapperBase(deliveryAdvice),
    m_ResultSet(resultSet)
{
}

DeliveryAdviceSQLMapper::~DeliveryAdviceSQLMapper()
{
}
const basar::VarString DeliveryAdviceSQLMapper::getSelectByDateRangeSQL(
    const basar::VarString& dbName,
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    const enum ConfirmationStatusEnum& confirmationStatus,
    const basar::Date& searchPeriodStart,
    const basar::Date& searchPeriodEnd)
{
    std::stringstream sSql;

    sSql << getCommonSelectPartSQL(dbName, branchNo, customerNo, false) << " AND "
            "h.completed > 0 AND "
            "h.deliveryadvicedate BETWEEN " << searchPeriodStart.getDate() << " AND " << searchPeriodEnd.getDate();
    if (confirmationStatus == CONFIRMATION_STATUS_ALL_UNCONFIRMED)
    {
        sSql << " AND h.confirmed = 0";
    }
    return sSql.str();
}

const basar::VarString DeliveryAdviceSQLMapper::getSelectByKeySQL(
    const basar::VarString& dbName,
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    const basar::Date& deliveryAdviceDate,
    const basar::VarString& deliveryAdviceNo,
    const basar::Int32& cscOrderNo,
    const bool& completedOnly)
{
    std::stringstream sSql;

    sSql << getCommonSelectPartSQL(dbName, branchNo, customerNo, true);
;
    if (true == completedOnly)
    {
        sSql << " AND h.completed > 0";
    }
    if (deliveryAdviceDate.isValid())
    {
        sSql << " AND h.deliveryadvicedate = " << deliveryAdviceDate.getDate();
    }
    if (false == deliveryAdviceNo.empty())
    {
        sSql << " AND h.deliveryadviceno = '" << deliveryAdviceNo << "'";
    }
    else if (cscOrderNo > 0)
    {
        sSql << " AND h.cscorderno = " << cscOrderNo;
    }
    sSql << " ORDER BY h.deliveryadvicedate DESC";
    return sSql.str();
}

const basar::VarString DeliveryAdviceSQLMapper::getCommonSelectPartSQL(
    const basar::VarString& dbName, const basar::Int16& branchNo, const basar::Int32& customerNo, const bool onlyFirstResult)
{
    std::stringstream sql;

    sql <<
        "SELECT " << (onlyFirstResult ? "FIRST 1 " : "") <<
        "h.branchno, "
        "h.customerno, "
        "h.deliveryadvicedate, "
        "h.deliveryadviceno, "
        "h.pharmosorderno, "
        "h.cscorderno, "
        "h.completed, "
        "h.specialdocumenttype, "
        "h.tourid, "
        "h.duedate, "
        "h.ordertype, "
        "h.pickingtype, "
        "h.bookingtype, "
        "h.requested, "
        "h.confirmed, "
        "h.orderlabel, "
        "h.cancelled, "
        "h.batchcorrectionadvice, "
        "h.linefee, "
        "h.packagefee, "
        "h.contractid, "
        "NVL(t.depositvalue, 0.0) AS depositvalue, "
        "NVL(t.netturnover, 0.0) AS netturnover, "
        "NVL(t.discountretail, 0.0) AS discountretail, "
        "NVL(t.discountwholesale, 0.0) AS discountwholesale, "
        "NVL(t.vatamount, 0.0) AS vatamount, "
        "NVL(t.logisticservicecost, 0.0) AS logisticservicecost, "
        "NVL(a.documentid, '') AS documentid "
        "FROM " << dbName << ":deliveryadvicehead h "
        "LEFT OUTER JOIN " << dbName << ":deliveryadvicetotals t ON "
        "   h.branchno=t.branchno AND "
        "   h.customerno=t.customerno AND "
        "   h.deliveryadvicedate=t.deliveryadvicedate AND "
        "   h.deliveryadviceno=t.deliveryadviceno "
        "LEFT OUTER JOIN " << dbName << ":documentarchiveinfo a ON "
        "   h.branchno=a.branchno AND "
        "   h.customerno=a.customerno AND "
        "   h.deliveryadvicedate=a.documentdate AND "
        "   h.deliveryadviceno=a.documentno AND "
        "   a.documenttype=1 "
        "WHERE "
        "   h.branchno=" << branchNo << " AND "
        "   h.customerno=" << customerNo;
    return sql.str();
}

const basar::VarString DeliveryAdviceSQLMapper::getSelectDnNumbersByReferencesSQL(
    const basar::VarString& dbName,
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    const std::vector<std::string>& deliveryAdviceReferences)
{
    if (deliveryAdviceReferences.empty())
    {
        return "";
    }
    std::vector<std::string>::const_iterator iter = deliveryAdviceReferences.begin();
    std::stringstream sIn;
    sIn << "'" << *iter++ << "'";
    while (iter != deliveryAdviceReferences.end())
    {
        sIn << ",'" << *iter++ << "'";
    }

    std::stringstream sSql;

    sSql <<
        "SELECT DISTINCT h.deliveryadviceno "
        "FROM " << dbName << ":deliveryadviceremark r "
        "INNER JOIN " << dbName << ":deliveryadvicehead h ON "
        "   h.branchno=r.branchno AND "
        "   h.customerno=r.customerno AND "
        "   h.deliveryadvicedate=r.deliveryadvicedate AND "
        "   h.cscorderno=r.cscorderno "
        "WHERE r.branchno=" << branchNo << " "
        "  AND r.customerno=" << customerNo << " "
        "  AND r.remarktype=15 "
        "  AND ((LENGTH(r.remarktext) > 6 AND SUBSTR(r.remarktext, 7) IN (" << sIn.str() << ")) OR r.remarktext IN (" << sIn.str() << "))";
    return sSql.str();
}

const basar::VarString DeliveryAdviceSQLMapper::getSelectForBatchAdvice(const basar::VarString& dbName, const basar::Int16& branchNo, const bool& batchCorrectionOnly)
{
    std::stringstream sSql;

    /*
    SELECT DISTINCT h.branchno, h.customerno, h.deliveryadvicedate, h.deliveryadviceno FROM deliveryadvicehead h
    INNER JOIN deliveryadviceline l ON l.branchno = h.branchno AND l.customerno = h.customerno AND l.deliveryadvicedate = h.deliveryadvicedate AND l.deliveryadviceno = h.deliveryadviceno
    LEFT JOIN deliveryadvicelinedetails d ON d.branchno = l.branchno AND d.customerno = l.customerno AND d.deliveryadvicedate = l.deliveryadvicedate AND d.pharmosorderno = l.pharmosorderno AND d.pharmosorderposno = l.pharmosorderposno
    LEFT JOIN deliveryadvicelineibtlink i ON i.branchno = l.branchno AND i.customerno = l.customerno AND i.deliveryadvicedate = l.deliveryadvicedate AND i.deliveryadviceno=l.deliveryadviceno AND i.deliveryadviceposno = l.deliveryadviceposno
    LEFT JOIN deliveryadviceline li ON li.branchno = i.ibtbranchno AND li.customerno = i.ibtcustomerno AND li.deliveryadvicedate = i.ibtdeliveryadvicedate AND li.deliveryadviceno = i.ibtdeliveryadviceno AND li.deliveryadviceposno = i.ibtdeliveryadviceposno
    LEFT JOIN deliveryadvicelinedetails di ON di.branchno=li.branchno and di.customerno=li.customerno AND di.deliveryadvicedate = li.deliveryadvicedate AND di.pharmosorderno = li.pharmosorderno AND di.pharmosorderposno = li.pharmosorderposno
    WHERE h.branchno= 51 AND h.completed= 1 AND h.batchcorrectionadvice < 3
    AND nvl(d.precalcbatchchanged,nvl(di.precalcbatchchanged,0)) = 1
    ORDER BY h.deliveryadvicedate DESC
    */

    sSql <<
        "SELECT DISTINCT h.branchno, h.customerno, h.deliveryadvicedate, h.deliveryadviceno FROM " << dbName << ":deliveryadvicehead h "
             "JOIN " << dbName << ":deliveryadviceline l         ON l.branchno=h.branchno     AND l.customerno=h.customerno     AND l.deliveryadvicedate=h.deliveryadvicedate     AND l.deliveryadviceno=h.deliveryadviceno "
        "LEFT JOIN " << dbName << ":deliveryadvicelinedetails d  ON d.branchno=l.branchno     AND d.customerno=l.customerno     AND d.deliveryadvicedate=l.deliveryadvicedate     AND d.pharmosorderno=l.pharmosorderno         AND d.pharmosorderposno=l.pharmosorderposno "
        "LEFT JOIN " << dbName << ":deliveryadvicelineibtlink i  ON i.branchno=l.branchno     AND i.customerno=l.customerno     AND i.deliveryadvicedate=l.deliveryadvicedate     AND i.deliveryadviceno=l.deliveryadviceno     AND i.deliveryadviceposno=l.deliveryadviceposno "
        "LEFT JOIN " << dbName << ":deliveryadviceline li        ON li.branchno=i.ibtbranchno AND li.customerno=i.ibtcustomerno AND li.deliveryadvicedate=i.ibtdeliveryadvicedate AND li.deliveryadviceno=i.ibtdeliveryadviceno AND li.deliveryadviceposno=i.ibtdeliveryadviceposno "
        "LEFT JOIN " << dbName << ":deliveryadvicelinedetails di ON di.branchno=li.branchno   and di.customerno=li.customerno   AND di.deliveryadvicedate = li.deliveryadvicedate AND di.pharmosorderno=li.pharmosorderno       AND di.pharmosorderposno = li.pharmosorderposno "
        "WHERE h.branchno= " << branchNo << " AND h.completed= 1 AND h.batchcorrectionadvice < 3 ";

    if (batchCorrectionOnly)
    {
        sSql << "AND nvl(d.precalcbatchchanged,nvl(di.precalcbatchchanged,0)) = 1 ";
    }
    sSql << "ORDER BY h.deliveryadvicedate DESC ";

    return sSql.str();
}

//----------------------------------------------------------------------------------
// UPDATE
//----------------------------------------------------------------------------------
const basar::VarString DeliveryAdviceSQLMapper::getUpdateSQL( const basar::VarString& dbName, const DeliveryAdvicePtr deliveryAdvice )
{
    std::stringstream sSql;

    sSql <<
        "UPDATE " << dbName << ":deliveryadvicehead SET ";

    bool setComma = false;

    if (!deliveryAdvice->getRequested().isUnset())
    {
        sSql << "requested = " << deliveryAdvice->getRequested().get();
        setComma = true;
    }

    if (!deliveryAdvice->getConfirmed().isUnset())
    {
        if (setComma)
        {
            sSql << ", confirmed = " << deliveryAdvice->getConfirmed().get();
        }
        else
        {
            sSql << "confirmed = " << deliveryAdvice->getConfirmed().get();
            setComma = true;
        }
    }

    if (!deliveryAdvice->getCompleted().isUnset())
    {
        if (setComma)
        {
            sSql << ", completed = '" << deliveryAdvice->getCompleted().c_str() << "' ";
        }
        else
        {
            sSql << "completed = '" << deliveryAdvice->getCompleted().c_str() << "' ";
            setComma = true;
        }
    }

    if (!deliveryAdvice->getCancelled().isUnset())
    {
        if (setComma)
        {
            sSql << ", cancelled =  " << deliveryAdvice->getCancelled().get();
        }
        else
        {
            sSql << "cancelled =  " << deliveryAdvice->getCancelled().get();
            setComma = true;
        }
    }

    if (!deliveryAdvice->getBatchCorrectionAdvice().isUnset())
    {
        if (setComma)
        {
            sSql << ", batchcorrectionadvice = " << deliveryAdvice->getBatchCorrectionAdvice().get();
        }
        else
        {
            sSql << "batchcorrectionadvice = " << deliveryAdvice->getBatchCorrectionAdvice().get();
            setComma = true;
        }
    }

    sSql << " WHERE branchno = " << deliveryAdvice->getBranchNo() << " and customerno = " << deliveryAdvice->getCustomerNo() << " and deliveryadvicedate = " << deliveryAdvice->getDeliveryAdviceDate().getDate() <<
        " and deliveryadviceno = '" << deliveryAdvice->getDeliveryAdviceNo() << "'" ;

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceSQLMapper::doMap()
{
    if( m_ResultSet.isNull() )
    {
        throw;
    }

    setBranchNo             (m_ResultSet.getInt16("branchno"));
    setCustomerNo           (m_ResultSet.getInt32("customerno"));
    setDeliveryAdviceDate   (basar::Date(m_ResultSet.getInt32("deliveryadvicedate")));
    setDeliveryAdviceNo     (m_ResultSet.getString("deliveryadviceno"));

    setPharmosOrderNo       (m_ResultSet.getInt32("pharmosorderno"));
    setCSCOrderNo           (m_ResultSet.getInt32("cscorderno"));
    setCompleted            (m_ResultSet.getString("completed"));
    setSpecialDocumentType  (m_ResultSet.getString("specialdocumenttype"));
    setTourId               (m_ResultSet.getString("tourid"));
    setDueDate              (basar::Date(m_ResultSet.getInt32("duedate")));
    setOrderType            (m_ResultSet.getString("ordertype"));
    setPickingType          (m_ResultSet.getString("pickingtype"));
    setBookingType          (m_ResultSet.getString("bookingtype"));
    setRequested            (m_ResultSet.getInt16("requested"));
    setConfirmed            (m_ResultSet.getInt16("confirmed"));
    setOrderLabel           (m_ResultSet.getString("orderlabel"));
    setCancelled            (m_ResultSet.getInt16("cancelled"));
    setBatchCorrectionAdvice(m_ResultSet.getInt16("batchcorrectionadvice"));
    setLineFee              (m_ResultSet.getDecimal("linefee"));
    setPackageFee           (m_ResultSet.getDecimal("packagefee"));
    setContractId           (m_ResultSet.getString("contractid"));

    setDepositValue         (m_ResultSet.getDecimal("depositvalue"));
    setNetTurnover          (m_ResultSet.getDecimal("netturnover"));
    setDiscountRetail       (m_ResultSet.getDecimal("discountretail"));
    setDiscountWholesale    (m_ResultSet.getDecimal("discountwholesale"));
    setVatAmount            (m_ResultSet.getDecimal("vatamount"));
    setLogisticServiceCost  (m_ResultSet.getDecimal("logisticservicecost"));

    setDocumentId           (m_ResultSet.getString("documentid"));
}

void DeliveryAdviceSQLMapper::doMapKeysOnly()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setBranchNo(m_ResultSet.getInt16("branchno"));
    setCustomerNo(m_ResultSet.getInt32("customerno"));
    setDeliveryAdviceDate(basar::Date(m_ResultSet.getInt32("deliveryadvicedate")));
    setDeliveryAdviceNo(m_ResultSet.getString("deliveryadviceno"));
}

} // end namespace document
} // end namespace libcsc
