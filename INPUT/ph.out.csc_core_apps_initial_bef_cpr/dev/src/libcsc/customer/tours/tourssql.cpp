#include <customer/tours/tourssql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

ToursSql::ToursSql()
{
}

ToursSql::~ToursSql()
{
}

const basar::VarString ToursSql::getToursQuery(
    const basar::Int32 branchNo, const basar::Int32 tourDate)
{
    std::stringstream sSql;
    sSql <<
        "SELECT distinct (tpt.tourid) " <<
        "FROM tourplantag tpt " <<
        "WHERE tpt.tourinaktiv = '0' AND tpt.tourinaktiv != '1' " <<
        "AND tpt.vertriebszentrumnr = " << branchNo << " AND  tpt.datumkommi = " << tourDate;

    return sSql.str();
}

const basar::VarString ToursSql::getCustomerToursInfoQuery(
    const basar::Int16 branchNo, const basar::Int32 tourDate, const std::vector<std::string>& tourIds, const basar::VarString& dbNameWarehouse)
{
    std::stringstream sSql;

    //Create IDS list for sql statement
    std::string inList("");
    for (size_t i = 0; i < tourIds.size(); i++)
    {
        if (i != 0)
            inList.append(",");

        inList.append(tourIds.at(i));
    }

    sSql << "SELECT DISTINCT  tpt.tourid AS tourid, tpt.idfnr AS idfnr, t.datumversand AS datumversand, t.zeitversand AS zeitversand, tpt.fahrtzeit AS fahrtzeit," << " "
        << "CASE WHEN tpt.idfnr = transmed.idfnr THEN 1 ELSE 0 END ::SMALLINT AS delivered" << " " // For missing entries in transmedtotestatus table
        << "FROM tour t" << " "
        << "JOIN tourplantag tpt  ON t.tourid=tpt.tourid AND t.filialnr=tpt.vertriebszentrumnr AND t.datumkommi=tpt.datumkommi" << " "
        << "JOIN kdauftrag kd ON tpt.idfnr = kd.idfnr AND tpt.tourid = kd.tourid AND kd.filialnr = tpt.vertriebszentrumnr" << " " // Only customers which has orders
        << "LEFT JOIN (" << " " // subquery starts
        << "SELECT DISTINCT tts.customerno AS idfnr, dk.tsv_tour AS tourid" << " "
        << "FROM " << dbNameWarehouse << ":dktsv dk" << " "
        << "JOIN " << dbNameWarehouse << ":transmedtotestatus tts ON dk.tsv_vsw_tm_barcode = tts.trackingbarcode AND dk.tsv_tran_date = tts.pickingdate" << " "
        << "AND dk.tsv_fil = tts.branchno AND dk.tsv_vsw_idf = tts.customerno" << " "
        << "WHERE dk.tsv_tour IN (" << inList << ") AND dk.tsv_tran_date = " << tourDate << " AND tts.branchno = " << branchNo << " "
        << "AND tts.stateid IN (SELECT tms.id  FROM " << dbNameWarehouse << ":transmedstatus tms WHERE tms.categoryid = 3)" << " "
        << ") transmed" << " " // subquery ends
        << "ON transmed.idfnr = tpt.idfnr AND transmed.tourid = tpt.tourid" << " "
        << "WHERE tpt.tourinaktiv = '0' AND t.tourinaktiv != '1' AND tpt.vertriebszentrumnr = " << branchNo << " "
        << "AND tpt.tourid IN (" << inList << ") AND tpt.datumkommi = " << tourDate << " ";

    return sSql.str();
}

} // end namespace customer
} // end namespace libcsc
