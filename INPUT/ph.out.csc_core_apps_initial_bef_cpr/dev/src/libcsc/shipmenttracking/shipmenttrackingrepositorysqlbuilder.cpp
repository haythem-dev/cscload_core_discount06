#include <shipmenttracking/shipmenttrackingrepositorysqlbuilder.h>
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"

#include <libbasarcmnutil.h>
#include <libbasarcmnutil_timespan.h>
#include <persistence/iaccessor.h>
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <boost/make_shared.hpp>


namespace libcsc {
namespace shipmenttracking {

//----------------------------------------------------------------------------------
// Get SQL Statement to query Shipment Tracking Tour Content Information from Outbound database
//----------------------------------------------------------------------------------
const basar::VarString ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectSQL(
    const ShipmentTrackingRequestProcessingContext& context
)
{
    bool takeJustArchiveForToteDelivery = false;
    if (context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ToteDeliveryMode)
    {
        // This part of logic is based on the results of an IFX DB data analysis, comparing (a)kdauftragpostour.deliverydate with akdauftrag.datum / kdauftragereignis(e11).datum_rechnung
        basar::Date maxDaysAgoDateForDeliveryInCurrentDayTables(context.Filter.getCurrentDate());
        maxDaysAgoDateForDeliveryInCurrentDayTables.addDays(-3);

        if (context.Filter.ToteDeliveryDate < maxDaysAgoDateForDeliveryInCurrentDayTables)
        {
            takeJustArchiveForToteDelivery = true;
        }
    }

    std::stringstream sSql;

    bool curreentDaySqlTaken = false;
    if ((context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ToteDeliveryMode && !takeJustArchiveForToteDelivery) ||
        context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::CurrentPickingDate
        )
    {
        getOutboundDataSelectForCurrentDayTables(
            context,
            sSql
        );

        curreentDaySqlTaken = true;
    }

    if (context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ToteDeliveryMode ||
        context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ArchivedPickingDate
        )
    {
        if (curreentDaySqlTaken)
        {
            sSql << std::endl  << " UNION " << std::endl;
        }

        getOutboundDataSelectForArchiveTables(
            context,
            sSql
        );
    }

    //NOTE: this SQL sorted sequence is important, because the OrderPosNr and WHS-TotePosNo are closely related. See the comparison: "201123-KscPosNr~=TSV_Pos"
    if (context.Filter.DetailsDesired)
    {
        sSql << std::endl << " ORDER BY ir.ibtorderno, ir.ibtorderposno, a.kdauftragnr, p.posnr; ";
    }
    else
    {
        sSql << std::endl << " ORDER BY ir.ibtorderno, a.kdauftragnr; ";
    }

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Get SQL Statement to query TourIDs belonging to branch for a certain date
//----------------------------------------------------------------------------------
const basar::VarString ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectSQLTourIDs(const ShipmentTrackingRequestProcessingContext& context, const basar::Int32& TourDate)
{
    std::stringstream sSql;
    sSql <<
        "SELECT distinct (tpt.tourid) " <<
        "FROM tourplantag tpt " <<
        "WHERE tpt.tourinaktiv = '0' AND tpt.tourinaktiv != '1' " <<
        "AND tpt.vertriebszentrumnr = " << context.BranchNo << " AND  tpt.datumkommi = " << TourDate;

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Get SQL Statement to query IDFs belonging to a Shipment Tracking TourID from Outbound database
//----------------------------------------------------------------------------------
const basar::VarString ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectSQLTourID_IDFS(const ShipmentTrackingRequestProcessingContext& context, const std::vector<std::string>& tourIDs, const basar::Int32& TourDate)
{

    std::stringstream sSql;

    //Create IDS list for sql statement
    std::string inList("");
    for (size_t i = 0; i < tourIDs.size(); i++)
    {
       if(i != 0) 
        inList.append(",");

        inList.append(tourIDs.at(i));
    }

    sSql << "SELECT tpt.tourid, tpt.idfnr from tourplantag tpt where " <<
        " tpt.vertriebszentrumnr = " << context.BranchNo <<
        " and tpt.tourid in (" << inList << ") and tpt.datumkommi = " << TourDate
        << " and  tpt.idfnr in (SELECT DISTINCT(IDFNR) from kdauftrag kd WHERE kd.filialnr = " << context.BranchNo << " ) ";

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Get SQL Statement part for current day
//----------------------------------------------------------------------------------
void ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectForCurrentDayTables(
    const ShipmentTrackingRequestProcessingContext& context,
    std::stringstream& sSql
)
{
    // Aktuelle TnT Daten + (Aktuell / Archiv) IBT
    sSql <<
        "SELECT "
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            "DISTINCT "
            ;
    }

    sSql <<
        "a.kdauftragnr as CscOrderNo "
        ;

    if (context.Filter.SendPharmosOrderNumbers)
    {
        sSql <<
            ", a.kdauftragnrfiliale as PharmosOrderNo "
            ;
    }

    sSql <<
        ", a.rechnungnr as DeliveryAdviceNo "
        ", e11.datum as e11date "
        ", e11.zeit as e11time " // == OrderClosedAt
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", p.posnr "
            ", NVL(ir.ibtconfirmedqty, p.mengegeliefert) as ExpectedDeliveryQuantity "
            ;
    }

    sSql <<
        // the: t.deliverydate & t.deliverytime == PlannedTimeOfArrival
        ", case when e11.datum is not null then ta.tourid "                                       // if the order is closed, it is tour purified, so take posnr=0. Everything which shall go with other tours was already split before E11!
        "       when i.cscorderposno is not null then NVL(ti.tourid, NVL(tp.tourid, ta.tourid)) " // else if IBT: nimm die verbundtour wenn vorhanden, sonst die postionstour wenn vorhanden, sonst die auftragstour
        "       else NVL(tp.tourid, ta.tourid) end as touridxori "                                // else if NO IBT: nimm die postionstour wenn vorhanden, sonst die auftragstour
        ", case when e11.datum is not null then ta.deliverydate "
        "       when i.cscorderposno is not null then NVL(ti.deliverydate, NVL(tp.deliverydate, ta.deliverydate)) "
        "       else NVL(tp.deliverydate, ta.deliverydate) end as deliverydatexori "
        ", case when e11.datum is not null then ta.deliverytime "
        "       when i.cscorderposno is not null then NVL(ti.deliverytime, NVL(tp.deliverytime, ta.deliverytime)) "
        "       else NVL(tp.deliverytime, ta.deliverytime) end as deliverytimexori "
        ", case when bitand(az.etartklasse1, 512) = 512 then 1 else 0 end as isNarcotic"
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", az.artikel_name "
            ", NVL(c.article_code, p.artikel_nr) as article_code "
            ", p.artikel_nr " // used in later statements for joining the DKTSV positions (the temporary status on 06.11.2020)
            ;
    }

    sSql <<
        // ~~~~~~~~~~~~~~~~~~~
        // IBT part from here:
        ", i.ibtbranchno "
        ", i.ibtcustomerno "
        ", ir.ibtorderno as iCscOrderNo "
        ;

    if (context.Filter.SendPharmosOrderNumbers)
    {
        sSql <<
            ", NVL(aibtc.kdauftragnrfiliale, aibta.kdauftragnrfiliale) as iPharmosOrderNo "
            ;
    }

    sSql <<
        ", NVL(aibtc.rechnungnr, aibta.rechnungnr) as iDeliveryAdviceNo "
        ", NVL(e11ibtc.datum, e11ibta.datum) as ie11date "
        ", NVL(e11ibtc.zeit, e11ibta.zeit) as ie11time " // == IbtOrderClosedAt
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", ir.ibtorderposno "
            ;
    }

    sSql <<
        // (a)kdauftragpostour ==> IbtPlannedTimeOfArrival:
        ", case when tibtca.tourid is null     then tibta.tourid  " // if there is no current kdauftragpostour (posnr=0), then try to use the archive: akdauftragpostour's tourid
        "       when e11ibtc.datum is not null then tibtca.tourid " // else, if the current kdauftrag order is closed, then it is tour purified, so take posnr=0. Everything which shall go with other tours was already split before E11!
        "       else NVL(tibtcp.tourid, tibtca.tourid)            " // else, from the current kdauftragpostour nimm die postionstour wenn vorhanden, sonst die auftragstour
        "       end as itouridxori "
        ", case when tibtca.deliverydate is null then tibta.deliverydate "
        "       when e11ibtc.datum is not null   then tibtca.deliverydate "
        "       else NVL(tibtcp.deliverydate, tibtca.deliverydate) "
        "       end as ideliverydatexori "
        ", case when tibtca.deliverytime is null then tibta.deliverytime "
        "       when e11ibtc.datum is not null   then tibtca.deliverytime "
        "       else NVL(tibtcp.deliverytime, tibtca.deliverytime) "
        "       end as ideliverytimexori "
        // ~~~~~~~~~~~~~~~~~~~
        "FROM " << context.DbNameOutbound << ":kdauftrag a "
        "join " << context.DbNameOutbound << ":kdauftragereignis e110 on e110.kdauftragnr=a.kdauftragnr and e110.ereignisart=110  " // order start date and time
        "left join " << context.DbNameOutbound << ":kdauftragereignis e11 on e11.kdauftragnr=a.kdauftragnr and e11.ereignisart=11 " // optional: oder closed at date and time, i.e. order could be still open
        "join " << context.DbNameOutbound << ":kdauftragpos p on p.kdauftragnr=a.kdauftragnr "
        "join      " << context.DbNameOutbound << ":kdauftragpostour ta on ta.kdauftragnr=a.kdauftragnr and ta.posnr=0       and ta.deliverybranchno=0 " // Auftragstour (posnr=0)
        "left join " << context.DbNameOutbound << ":kdauftragpostour tp on tp.kdauftragnr=p.kdauftragnr and tp.posnr=p.posnr and tp.deliverybranchno=0 " // Positionstour (posnr>0,deliverybranchno=0)
        "left join " << context.DbNameOutbound << ":kdauftragpostour ti on ti.kdauftragnr=p.kdauftragnr and ti.posnr=p.posnr and ti.deliverybranchno>0 " // Verbundtour zum Kunden (posnr>0,deliverybranchno>0)
        "join " << context.DbNameOutbound << ":artikelzentral az on az.artikel_nr=p.artikel_nr "
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            "LEFT JOIN " << context.DbNameOutbound << ":articlecodes c ON c.articleno = p.artikel_nr AND c.preferred_flag = 1 "
            ;
    }

    // ~~~~~~~~~~~~~~~~~~~
    // IBT part from here.
    sSql <<
        "left join " << context.DbNameOutbound << ":ibtrequest i on i.branchno=a.vertriebszentrumnr and i.cscorderno=a.kdauftragnr and i.cscorderposno=p.posnr and to_char(i.creationdatetime,'%Y%m%d') >= e110.datum and i.customerno=a.kundennr "
        "left join " << context.DbNameOutbound << ":ibtresponse ir on ir.ibtrequestid=i.ibtrequestid "
        // Try get current i.e. not archived IBT kdauftrag - alternative #1:
        "left join " << context.DbNameOutbound << ":kdauftrag aibtc on aibtc.kdauftragnr=ir.ibtorderno "
        "left join " << context.DbNameOutbound << ":kdauftragereignis e11ibtc on e11ibtc.kdauftragnr=aibtc.kdauftragnr and e11ibtc.ereignisart=11 "
        "left join " << context.DbNameOutbound << ":kdauftragpostour tibtca on tibtca.kdauftragnr=aibtc.kdauftragnr and tibtca.posnr=0                and tibtca.deliverybranchno=0 " // Auftragstour (posnr=0)
        "left join " << context.DbNameOutbound << ":kdauftragpostour tibtcp on tibtcp.kdauftragnr=aibtc.kdauftragnr and tibtcp.posnr=ir.ibtorderposno and tibtcp.deliverybranchno=0 " // Positionstour (posnr>0,deliverybranchno=0)
        // Try get archived IBT akdauftrag - alternative #2:
        "left join " << context.DbNameOutbound << ":akdauftragposereignis peibta on peibta.datum=to_char(ir.creationdatetime,'%Y%m%d') and peibta.kdauftragnr=ir.ibtorderno and peibta.posnr=ir.ibtorderposno "
        "left join " << context.DbNameOutbound << ":akdauftrag aibta on aibta.datum=peibta.datum_rechnung and aibta.kdauftragnr=ir.ibtorderno "
        "left join " << context.DbNameOutbound << ":akdauftragereignis e11ibta on e11ibta.datum_rechnung=aibta.datum and e11ibta.kdauftragnr=aibta.kdauftragnr and e11ibta.ereignisart=11 "
        "left join " << context.DbNameOutbound << ":akdauftragpostour tibta on tibta.datum = aibta.datum and tibta.kdauftragnr=aibta.kdauftragnr and tibta.posnr = 0 " // NOTE: if the order is closed, it is tour purified. Everything which shall go with other tours was already split before E11!
        // ~~~~~~~~~~~~~~~~~~~
        "WHERE a.vertriebszentrumnr = " << context.BranchNo << " and a.kundennr = " << context.CustomerNo << " "
        ;

    if (context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ToteDeliveryMode)
    {
        sSql <<
            "AND " << context.Filter.ToteDeliveryDate.getDate() <<
            "             = (case when e11.datum is not null then ta.deliverydate "          // "deliverydate" expected in format: 20191123
            "                     when i.cscorderposno is not null then NVL(ti.deliverydate, NVL(tp.deliverydate, ta.deliverydate)) "
            "                     else NVL(tp.deliverydate, ta.deliverydate) "
            "                end) "
            ;
    }
    else
    {
        //NOTE: to get also the not closed orders, do not filter according a date here!
        //sSql << "and e11.datum=" << zzz << " ";
    }

    if (!context.Filter.SpecificTourID.empty() &&
        // Efficient way to check if std::string has only spaces:
        // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces/36535031
        context.Filter.SpecificTourID.find_first_not_of(' ') != std::string::npos
        )
    {
        // context.Filter.SpecificTourID is filled and there's a non-space, so query today's data:

        //NOTE: taking planned tour instead of real tour in the filtering for a tour ensures, that all the redirection info is collected always together!
        //      In other case you have to modify the big statement, in adding 1 more join per each of the 3: ibtd, d1 and d2 DKTSV tables for chosing additional info inherent for each row.
        //      It would just be pretty more confusing to understand the big SELECT, so I have chosen this more natural way: the way to look at the data, as the customer ordered it and as it was promissed to him fom PHX during the ordering...

        sSql <<
            //NOTE: real tour query:
            //"AND " << context.Filter.SpecificTourID << " = (case when e11.datum is not null then NVL(d1.tsv_tour, NVL(d2.tsv_tour, ta.tourid)) " // if the order is closed, it is tour purified, so take posnr=0. Everything which shall go with other tours was already split before E11!

            //NOTE: panned tour query:
            "AND " << context.Filter.SpecificTourID << " = (case when e11.datum is not null then ta.tourid "  // if the order is closed, it is tour purified, so take posnr=0. Everything which shall go with other tours was already split before E11!
            "       when i.cscorderposno is not null then NVL(ti.tourid, NVL(tp.tourid, ta.tourid)) " // else if IBT: nimm die verbundtour wenn vorhanden, sonst die postionstour wenn vorhanden, sonst die auftragstour
            "       else NVL(tp.tourid, ta.tourid) end) "
            ;
    }

    sSql << "AND a.kdauftragart!='PR' AND NVL(ir.ibtconfirmedqty, p.mengegeliefert) > 0 ";
}

//----------------------------------------------------------------------------------
// Get SQL Statement part for Archive
//----------------------------------------------------------------------------------
void ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectForArchiveTables(
    const ShipmentTrackingRequestProcessingContext& context,
    std::stringstream& sSql
)
{
    // Archiv TnT Daten + Archiv IBT
    sSql <<
        "SELECT "
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            "DISTINCT "
            ;
    }

    sSql <<
        "a.kdauftragnr as CscOrderNo "
        ;

    if (context.Filter.SendPharmosOrderNumbers)
    {
        sSql <<
            ", a.kdauftragnrfiliale as PharmosOrderNo "
            ;
    }

    sSql <<
        ", a.rechnungnr as DeliveryAdviceNo "
        ", e11.datum as e11date "
        ", e11.zeit as e11time " // == OrderClosedAt 
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", p.posnr "
            ", NVL(ir.ibtconfirmedqty, p.mengegeliefert) as ExpectedDeliveryQuantity "
            ;
    }

    sSql <<
        ", t.tourid as touridxori "
        ", t.deliverydate as deliverydatexori "
        ", t.deliverytime as deliverytimexori " // == PlannedTimeOfArrival
        ", case when bitand(az.etartklasse1, 512) = 512 then 1 else 0 end as isNarcotic"
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", az.artikel_name "
            ", NVL(c.article_code, p.artikel_nr) as article_code "
            ", p.artikel_nr " // used in later statements for joining the DKTSV positions (the temporary status on 06.11.2020)
            ;
    }

    sSql <<
        // ~~~~~~~~~~~~~~~~~~~
        // IBT part from here:
        ", i.ibtbranchno "
        ", i.ibtcustomerno "
        ", ir.ibtorderno as iCscOrderNo "
        ;

    if (context.Filter.SendPharmosOrderNumbers)
    {
        sSql <<
            ", aibt.kdauftragnrfiliale as iPharmosOrderNo "
            ;
    }

    sSql <<
        ", aibt.rechnungnr as iDeliveryAdviceNo "
        ", e11ibt.datum as ie11date "
        ", e11ibt.zeit as ie11time " // == IbtOrderClosedAt
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", ir.ibtorderposno "
            ;
    }

    sSql <<
        ", tibt.tourid as itouridxori "
        ", tibt.deliverydate as ideliverydatexori "
        ", tibt.deliverytime as ideliverytimexori " // == IbtPlannedTimeOfArrival
        // ~~~~~~~~~~~~~~~~~~~
        "FROM " << context.DbNameOutbound << ":akdauftrag a "
        "left join " << context.DbNameOutbound << ":akdauftragereignis e110 on e110.datum_rechnung=a.datum and e110.kdauftragnr=a.kdauftragnr and e110.ereignisart=110 "
        "left join " << context.DbNameOutbound << ":akdauftragereignis e11 on e11.datum_rechnung=a.datum and e11.kdauftragnr=a.kdauftragnr and e11.ereignisart=11 "
        "join " << context.DbNameOutbound << ":akdauftragpos p on p.datum=a.datum and p.kdauftragnr=a.kdauftragnr "
        "left join " << context.DbNameOutbound << ":akdauftragpostour t on t.datum = a.datum and t.kdauftragnr=a.kdauftragnr and t.posnr = 0 " // NOTE: if the order is closed, it is tour purified, so take posnr=0. Everything which shall go with other tours was already split before E11!
        "join " << context.DbNameOutbound << ":artikelzentral az on az.artikel_nr=p.artikel_nr "
        ;

    if (context.Filter.DetailsDesired)
    {
        sSql <<
            "LEFT JOIN " << context.DbNameOutbound << ":articlecodes c ON c.articleno = p.artikel_nr AND c.preferred_flag = 1 "
            ;
    }

    // ~~~~~~~~~~~~~~~~~~~
    // IBT part from here:
    sSql <<
        "left join " << context.DbNameOutbound << ":ibtrequest i on i.branchno=a.vertriebszentrumnr and i.cscorderno=a.kdauftragnr and i.cscorderposno=p.posnr and to_char(i.creationdatetime,'%Y%m%d') between e110.datum and e110.datum_rechnung and i.customerno=a.kundennr "
        "left join " << context.DbNameOutbound << ":ibtresponse ir on ir.ibtrequestid=i.ibtrequestid "
        "left join " << context.DbNameOutbound << ":akdauftragposereignis peibt on peibt.datum=to_char(ir.creationdatetime,'%Y%m%d') and peibt.kdauftragnr=ir.ibtorderno and peibt.posnr=ir.ibtorderposno "
        "left join " << context.DbNameOutbound << ":akdauftrag aibt on aibt.datum=peibt.datum_rechnung and aibt.kdauftragnr=ir.ibtorderno "
        "left join " << context.DbNameOutbound << ":akdauftragereignis e11ibt on e11ibt.datum_rechnung=aibt.datum and e11ibt.kdauftragnr=aibt.kdauftragnr and e11ibt.ereignisart=11 "
        "left join " << context.DbNameOutbound << ":akdauftragpostour tibt on tibt.datum = aibt.datum and tibt.kdauftragnr=aibt.kdauftragnr and tibt.posnr = 0 " // NOTE: if the order is closed, it is tour purified. Everything which shall go with other tours was already split before E11!
        ;

    // ~~~~~~~~~~~~~~~~~~~
    if (context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ToteDeliveryMode)
    {
        // from: (deliverydate - 9) to: (deliverydate + 5) <-- values derived from an IFX DB analysis, comparing (a)kdauftragpostour.deliverydate with akdauftrag.datum / kdauftragereignis(e11).datum_rechnung
        basar::Date lowerBoderOfPickingDate(context.Filter.ToteDeliveryDate);
        lowerBoderOfPickingDate.addDays(-9);

        basar::Date upperBoderOfPickingDate(context.Filter.ToteDeliveryDate);
        upperBoderOfPickingDate.addDays(5);

        sSql << "where a.datum between " << lowerBoderOfPickingDate.getDate() << " and " << upperBoderOfPickingDate.getDate() << " ";
    }
    else
    {
        sSql << "where a.datum = " << context.Filter.PickingDate.getDate() << " "   // "a.datum" expected in format: 20191123
            ;
    }

    sSql << "and a.vertriebszentrumnr = " << context.BranchNo << " and a.kundennr=" << context.CustomerNo << " ";

    if (context.Filter.getDateFilterMode() == ShipmentTrackingDataFilter::ToteDeliveryMode)
    {
        sSql << " and t.deliverydate=" << context.Filter.ToteDeliveryDate.getDate() << " ";     // "deliverydate" expected in format: 20191123
    }

    if (!context.Filter.SpecificTourID.empty() &&
        // Efficient way to check if std::string has only spaces:
        // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces/36535031
        context.Filter.SpecificTourID.find_first_not_of(' ') != std::string::npos
        )
    {
        // context.Filter.SpecificTourID is filled and there's a non-space, so query today's data:

        //NOTE: taking planned tour instead of real tour in the filtering for a tour ensures, that all the redirection info is collected always together!
        //      In other case you have to modify the big statement, in adding 1 more join per each of the 3: ibtd, d1 and d2 DKTSV tables for chosing additional info inherent for each row.
        //      It would just be pretty more confusing to understand the big SELECT, so I have chosen this more natural way: the way to look at the data, as the customer ordered it and as it was promissed to him fom PHX during the ordering...

        //NOTE: real tour query:
        //sSql << "AND NVL(d1.tsv_tour, NVL(d2.tsv_tour, t.tourid)) = " << context.Filter.SpecificTourID << " ";

        //NOTE: planned tour query
        sSql << "AND t.tourid = " << context.Filter.SpecificTourID << " ";
    }

    sSql << "AND a.kdauftragart!='PR' AND NVL(ir.ibtconfirmedqty, p.mengegeliefert) > 0 ";
}

//----------------------------------------------------------------------------------
// Get SQL Statement to query Shipment Tracking Tour Content Information from Warehouse database
//----------------------------------------------------------------------------------
const basar::VarString ShipmentTrackingRepositorySqlBuilder::getWarehouseDataSelectSQL(
    const ShipmentTrackingRequestProcessingContext& context,
    const Int32HashSetMap& pickingDateMap,
    const Int32HashSetMap& cscOrderNoMap
)
{
    if (pickingDateMap.size() < 1)
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingRepositorySqlBuilder::getWarehouseDataSelectSQL()", "pickingDateMap is empty. Nothing to look for!", __FILE__, __LINE__), "");
    }
    if (cscOrderNoMap.size() < 1)
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingRepositorySqlBuilder::getWarehouseDataSelectSQL()", "cscOrderNoMap is empty. Nothing to look for!", __FILE__, __LINE__), "");
    }

    std::string pickingDatesStr = stringJoinKeys(pickingDateMap, ", ");
    std::string cscOrderNosStr = stringJoinKeys(cscOrderNoMap, ", ");


    std::stringstream sSql;

    //NOTE: remote DB data fetch optimization on our own:
    sSql <<
        "SELECT "
        ;

    if (!context.Filter.DetailsDesired &&
        context.BranchNo > 0 //NOTE: this line is a fake usage of branchNo, just to satisfy compiler! Actually it should be used in the "AND (d.tsv_vsw_idf = cscOrderNo ..." below. But it is not necessary, because at one date, there can't be 2 customes from different branches having the same CscOrderNo!
        )
    {
        sSql <<
            "DISTINCT "
            "case when d.tsv_vsw_kzlk='V' then 0 else 1 end notIbtLocal, "
            ;
    }

    sSql <<
        "d.tsv_cscorderno, d.tsv_vsw_tm_barcode " // d.tsv_tran_date, , d.tsv_vbtran_date -> dates are unnecessary, because they are just a match to the Outbound's OrderClosedOn (OrderClosedAt.getDate())
        ", d.tsv_wannennr "
        ;

    if (context.Filter.SendPickingOrderNumbers)
    {
        sSql <<
            ", d.tsv_vsw_la, d.tsv_vsw_seite "
            ;
    }

    sSql <<
        ", d.tsv_status, d.tsv_vsw_kzlk "
        ", case when d.tsv_vsw_beipack='J' then 1 else 0 end as isContainer " //NOTE: this entry may, but does not make problems for a DISTINCT, if we do not need any details...
        ", case when d.tsv_vsw_btm='J' then 1 else 0 end as isNarcotic "      // necessary for line joining between Outbound and WHS data. There are normal and Narcotic Totes after Outbound DB data was read.
        ", d.tsv_tour, d.tsv_vsw_rtour, d.tsv_fahrzeit "
        ", d.insertdatetime "
        ;


    // ~~~~~~~~~~~~~~~~~~~
    // Line data: 
    if (context.Filter.DetailsDesired)
    {
        sSql <<
            ", d.tsv_pos, d.tsv_kop_pzn, d.tsv_kop_omenge " // necessary for line joining between Outbound and WHS data. If there are several positions with the same ArticleNo (PZN), then we look for first match of: NVL(ir.ibtconfirmedqty, p.mengegeliefert) == d.tsv_kop_omenge
            ", d.tsv_kop_meng, d.tsv_kop_charge "           // Line content
            ;
    }

    sSql <<
        "from " << context.DbNameWarehouse << ":dktsv d "
        "where d.tsv_tran_date in (" << pickingDatesStr << ") "
        "AND d.tsv_cscorderno in (" << cscOrderNosStr << ") "
        "AND (d.tsv_vsw_idf = " << context.CustomerNo << " OR d.tsv_vsw_vbidf = " << context.CustomerNo << ") " // <-- this condition line is necessary because of IBT CscOrderNo can be used for several different customers at one time!!
        "AND (d.tsv_status!=8 OR d.tsv_vsw_kzlk = 'V') " // ignore this unnecessary lines. The info is already contained in the right content DKTSV lines. BUT take it, in a case of (tsv_vsw_kzlk = 'V') - just for sure. Consider, there is no content lines for (tsv_vsw_kzlk = 'V')

        ;

    // ~~~~~~~~~~~~~~~~~~~
    // The order is very important - based on this no remove and replace of lines because of Tote State 1, 8 and 9, i.e. DKTSV.TSV_STATUS (== TSV-W-STATUS) is necessary:
    if (context.Filter.DetailsDesired)
    {
        sSql <<
            "ORDER BY case when d.tsv_status=9 then 1 else 0 end, case when d.tsv_vsw_kzlk='V' then 0 else 1 end, d.tsv_CscOrderNo, d.tsv_wannennr, d.tsv_pos, d.tsv_status desc, d.tsv_vsw_rtour desc; "
            ;
    }
    else
    {
        sSql <<
            "ORDER BY notIbtLocal, d.tsv_CscOrderNo , d.tsv_wannennr, d.tsv_status , d.tsv_vsw_rtour; "
            ;
    }

    return sSql.str();
}


} // end namespace shipmenttracking
} // end namespace libcsc
