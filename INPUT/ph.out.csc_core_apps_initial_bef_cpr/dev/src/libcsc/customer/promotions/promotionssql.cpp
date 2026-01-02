#include <customer/promotions/promotionssql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

PromotionsSql::PromotionsSql()
{
}

PromotionsSql::~PromotionsSql()
{
}

const basar::VarString PromotionsSql::GetPromotionsQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, basar::Int32 today)
{
    std::stringstream sql;
    sql << "SELECT NVL(q.customerquotaqty, -1) AS MaxQuantity1, NVL(qc.customerquotaqty, -1) AS MaxQuantity, "
        << "       NVL(qc.soldqtycst, -1) AS SoldQuantity, NVL(q.customerminqty, -1) AS MinQuantity, "
        << "       d.datefrom AS DateFrom, d.dateto AS DateTo, d.articleno AS ArticleNo, "
        << "       d.baseqty AS BaseQuantity, d.base_value AS BaseValue, "
        << "       d.discountvaluepct AS DiscountValuePercentage, d.discountqty AS DiscountQuantity, d.discountarticle AS DiscountArticle, "
        << "       d.discountspec AS DiscountSpecification, p.snotbysaleseweb AS NotViaSalesWeb, "
        << "       p.promotion_no AS PromotionNo, p.name AS Name "
        << "FROM discount d "
        << "INNER JOIN promotions p ON p.promotion_no=d.promotion_no AND p.promotion_type!=1 "
        << " LEFT JOIN promotionquota q ON q.promotion_no=p.promotion_no AND q.branchno=d.branchno AND q.articleno=d.articleno AND q.branchquotaqty=0 "
        << " LEFT JOIN promotionquotacst qc ON qc.promotion_no=p.promotion_no AND qc.branchno=d.branchno AND qc.articleno=d.articleno AND qc.customerno=" << customerNo << " "
        << "WHERE d.branchno=" << branchNo
        << "  AND d.promotion_no > 0 AND d.articleno > 0 AND d.manufacturerno=0 AND d.artcategoryno=0 "
        << "  AND d.discountgrpno=0 AND d.datefrom <= " << today  << " AND d.dateto >= " << today
        << "  AND (   d.customerno=" << customerNo
        << "       OR (    d.customerno=0 "
        << "           AND (   d.pharmacygroupid=0 "
        << "                OR d.pharmacygroupid IN (SELECT pharmacygroupid FROM customerpharmacygr WHERE branchno=" << branchNo << " AND customerno=" << customerNo << ") ) ) )";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
