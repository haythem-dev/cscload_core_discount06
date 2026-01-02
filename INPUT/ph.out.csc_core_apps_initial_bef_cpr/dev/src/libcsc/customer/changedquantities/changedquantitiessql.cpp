#include <customer/changedquantities/changedquantitiessql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

ChangedQuantitiesSql::ChangedQuantitiesSql()
{
}

ChangedQuantitiesSql::~ChangedQuantitiesSql()
{
}

const basar::VarString ChangedQuantitiesSql::GetChangedQuantitiesQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 dateFrom, const basar::Int32 dateTo)
{
    std::stringstream sql;
    sql << "SELECT * FROM ("
        << GetQuery(branchNo, customerNo, orderNo, dateFrom, dateTo, true)
        << " UNION "
        << GetQuery(branchNo, customerNo, orderNo, dateFrom, dateTo, false)
        << ") ORDER BY CustomerNo, OrderDate";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString ChangedQuantitiesSql::GetQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, bool archive)
{
    std::stringstream sql;
    sql << "SELECT auf.filialnr AS BranchNo, auf.idfnr AS CustomerNo, auf.kdauftragnr AS OrderNo, "
        <<      (archive ? "auf" : "e") << ".datum AS OrderDate, "
        <<      "auf.invoicenumber AS InvoiceNo, pos.artikel_nr AS ArticleNo, az.artikel_langname AS ArticleName, "
        <<      "pc.menge_alt AS QuantityOriginal, pc.mengebestaetigt AS QuantityNew, pc.mengebestellt AS QuantityOrdered "
        << "FROM " << (archive ? "akdauftragposchang" : "kdauftragposchange") << " pc "
        << "INNER JOIN " << (archive ? "a" : "") << "kdauftrag auf ON pc.kdauftragnr=auf.kdauftragnr "
        << "INNER JOIN " << (archive ? "a" : "") << "kdauftragpos pos ON pc.kdauftragnr=pos.kdauftragnr AND pc.posnr=pos.posnr "
        << "INNER JOIN artikelzentral az ON pos.artikel_nr=az.artikel_nr ";

    if (!archive)
    {
        sql << "INNER JOIN kdauftragereignis e ON e.kdauftragnr=pc.kdauftragnr ";
    }

    sql << GetWhere(branchNo, customerNo, orderNo, dateFrom, dateTo, archive);


    return sql.str();
}

const basar::VarString ChangedQuantitiesSql::GetWhere(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, bool archive)
{
    std::stringstream sql;
    sql << "WHERE auf.filialnr=" << branchNo;

    if (orderNo > 0)
    {
        sql << " AND auf.kdauftragnr=" << orderNo;
    }
    if (customerNo > 0)
    {
        sql << " AND auf.idfnr=" << customerNo;
    }

    if (archive)
    {
        sql << " AND auf.datum BETWEEN " << dateFrom << " AND " << dateTo;
    }
    else
    {
        sql << " AND e.ereignisart=1";
    }

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
