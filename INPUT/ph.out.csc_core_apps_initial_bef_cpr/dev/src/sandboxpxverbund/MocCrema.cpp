#include "MocCrema.h"
#include <sstream>
#include "SessionUtil.h"

#ifdef _AIX
#include <uuid.h>
#else // WIN32
#include <rpc.h>
#endif

const char* CremaWebUser = "Test.Buddy";

MocUserSuggestion::MocUserSuggestion(SessionUtil& session) : _session(session)
{
}

MocUserSuggestion::~MocUserSuggestion()
{
    // Teardown: Clean up resources
    cleanup();
}

short MocUserSuggestion::getBranchNo() const
{
    return branchno;
}

const char* MocUserSuggestion::getTestUser() const
{
    return CremaWebUser;
}

void MocUserSuggestion::cleanup()
{
    std::stringstream ssCremaWebUserSuggestion;
    ssCremaWebUserSuggestion << "DELETE FROM cremawebusersuggestion WHERE branchno = " << branchno << ";";
    _session.doSQL(ssCremaWebUserSuggestion.str());

    std::stringstream ssKdauftrag;
    ssKdauftrag << "DELETE FROM kdauftrag WHERE filialnr = " << branchno << ";";
    _session.doSQL(ssKdauftrag.str());
}

void MocUserSuggestion::createOrder(const int customerno, const int orderno)
{
    cleanup();

    std::stringstream ss;
    ss << "INSERT INTO kdauftrag (kdauftragnr, kdauftragstat, idfnr, geraetname, tourid, touridalt, personalnr, matchcode, rechnungnr, filialnr, etauftragschalter1, "
        << " etauftragschalter2, etauftragschalter3, etauftragschalter4, kdauftragart, koart, buchart, datumvaluta, wertauftrag, wertlieferung, wertzeilen, anzpos, "
        << " anzposob, anzposletzte, anzposdafue, anzposdafuefehler, anzalphatext, anzbtm, anzcontainer, anzbehaeltwechsel, anzbehaelt, anzsonderwanne, behaeltergewicht, "
        << " rabattbarproz, zeitendeam, zeitendepm, lagernrrechnung, auftragnrko, dmobilplatznr, skddefektabsagen, druckposition, batchschreiben, bemerkungen, kundetext, "
        << " herkunftfiliale, naechstetour, letztetour, dafueauftragnr, dafuegeraetename, vertriebszentrumnr, kundennr, kdauftragnrfiliale, sendestatus, pooltyp, poolnr, "
        << " zugrund, datumauslieferung, kdauftragnrorg, datumorg, kzrestored, batchauftragnr, sub_order_type, payment_term, anzauf, datumvalutabatch, valutamonauto, "
        << " valutamonmanuell, tenderno, datumversand, datumbtm, btmformularnr, wertnetto, wertrabatt, invoicenumber, paymentdate, paymenttype, etauftragschalter5, "
        << " etauftragschalter6, driverid, xmlreferenceno, logisticvolume, orderlabel, dpodays, orderperiodid, origintypeorg) "
        << "VALUES (" << orderno << ", '', " << customerno << ", '', '', '', 0, '', 0, " << branchno << ", 32768, 0, 0, 0, 'NO', '0', '0', 0, 63.72, 63.72, 63.72, 1, "
        << "0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0.00, 180000, 0, '', 0, 0, '', 0, 0, '', '', 0, '153028', '234421', 0, '', " << branchno << ", " << customerno << ", 0, 0, 0, "
        << "0, '0000010000000000', 20251013, 0, 0, '0', 0, '', '', 0, 0, 0, 0, 0, 20251013, 0, '', 0.00, 0.00, '', 0, '0', 0, 0, 0, '', 0, 'NORMAL', 0, 376981, 0);";

    _session.doSQL(ss.str());
}

// =======================================================================================================================================
// =======================================================================================================================================

const short CremaTypeId = 2;

MocOpenCremaOrder::MocOpenCremaOrder(SessionUtil& session) : _session(session)
{
}

MocOpenCremaOrder::~MocOpenCremaOrder()
{
    // Teardown: Clean up resources
    cleanup();
}

void MocOpenCremaOrder::cleanup()
{
    if (_uuid.empty())
    {
        return;
    }
    std::stringstream ss;
    ss << "DELETE FROM debtmailsend WHERE guid = '" << _uuid << "';";
    _session.doSQL(ss.str());
    _uuid.clear();
}

short MocOpenCremaOrder::createOpenCremaOrder()
{
    cleanup();

    const CremaDataSearchValues order = findOrderWithoutLimitBreach();

    const int smtpusergroupId = findSmtpusergroupId(order.branchno, CremaTypeId);

    createDebtmailsendEntry(order.branchno, order.orderno, smtpusergroupId, CremaTypeId);

    return order.branchno;
}

CremaDataSearchValues MocOpenCremaOrder::findOrderWithoutLimitBreach()
{
    std::stringstream ss;
    ss << "SELECT FIRST 1 a.kdauftragnr, a.vertriebszentrumnr "
       << "FROM kdauftrag a "
       << "INNER JOIN kunde k ON k.idfnr = a.idfnr "
       << "INNER JOIN debtlimit d ON d.partnerno = k.partnernr OR d.partnerno = k.maincstno "
       << "WHERE (SELECT COUNT('x') FROM debtmailsend dms WHERE dms.kdauftragnr = a.kdauftragnr AND dms.branchno = a.vertriebszentrumnr) = 0;";

    basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
    if (!result.next())
    {
        std::cout << "No order without limit breach found in database." << std::endl;
        throw;
    }

    CremaDataSearchValues order;
    order.orderno = result.getInt32("kdauftragnr");
    order.branchno = result.getInt16("vertriebszentrumnr");
    return order;
}

int MocOpenCremaOrder::findSmtpusergroupId(const short branchno, const short crematypeid)
{
    std::stringstream ss;
    ss << "SELECT id "
       << "FROM smtpusergroups "
       << "WHERE branchno = " << branchno << " AND crematypeid = " << crematypeid << ";";

    basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
    if (!result.next())
    {
        std::cout << "No order without limit breach found in database." << std::endl;
        throw;
    }

    return result.getInt32("id");
}

void MocOpenCremaOrder::createDebtmailsendEntry(const short branchno, const int orderno, const int smtpusergroupId, const short crematypeid)
{
    const basar::DateTime datetime = basar::cmnutil::DateTime::getCurrent();
    _uuid = generateUUID();

    std::stringstream ss;
    ss << "INSERT INTO debtmailsend (smtpusergroupid, kdauftragnr, guid, wassend, senddate, branchno, crematypeid, sendtime, partnerno, emailtype) "
       << "VALUES(" << smtpusergroupId << ", " << orderno << ", '" << _uuid << "', '1', " << datetime.getDate() << ", "
       << " " << branchno << " , " << crematypeid << ", " << datetime.getTime() / 1000 << ", 666, 0);";

    _session.doSQL(ss.str());
}

std::string MocOpenCremaOrder::generateUUID()
{
    uuid_t   uuid;
#ifdef _AIX
    unsigned32 status = 0;
    unsigned char* uuidBuff = 0;

    uuid_create(&uuid, &status);
    assert(status == uuid_s_ok);
    uuid_to_string(&uuid, &uuidBuff, &status);
    assert(status == uuid_s_ok);
    std::string suuid((char*)uuidBuff);
    free(uuidBuff);

    return suuid;
#else // WIN32
    RPC_STATUS status;
    unsigned char* uuidBuff = 0;

    status = UuidCreate(&uuid);
    assert(status == RPC_S_OK);
    status = UuidToString(&uuid, &uuidBuff);
    assert(status == RPC_S_OK);
    std::string suuid((char*)uuidBuff);
    RpcStringFree(&uuidBuff);

    return suuid;
#endif
}

// =======================================================================================================================================
// =======================================================================================================================================

MocFinishedTodayCremaOrder::MocFinishedTodayCremaOrder(SessionUtil& session) : _session(session)
{
}

MocFinishedTodayCremaOrder::~MocFinishedTodayCremaOrder()
{
    // Teardown: Clean up resources
    cleanup();
}

void MocFinishedTodayCremaOrder::cleanup()
{
    std::stringstream ss;
    ss << "DELETE FROM kdauftragdebtrel WHERE reluser = '" << CremaWebUser << "';";
    _session.doSQL(ss.str());
}

short MocFinishedTodayCremaOrder::createFinishedTodayCremaOrder()
{
    cleanup();

    const CremaDataSearchValues order = findOrderWithoutDebtRel();

    createDebtRelEntry(order.orderno);

    return order.branchno;
}

CremaDataSearchValues MocFinishedTodayCremaOrder::findOrderWithoutDebtRel()
{
    std::stringstream ss;
    ss << "SELECT FIRST 1 a.kdauftragnr, a.vertriebszentrumnr "
       << "FROM kdauftrag a "
       << "INNER JOIN kunde k ON k.idfnr = a.idfnr AND k.filialnr = a.vertriebszentrumnr "
       << "WHERE (SELECT COUNT('x') FROM kdauftragdebtrel dr WHERE a.kdauftragnr = dr.kdauftragnr) = 0;";

    basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
    if (!result.next())
    {
        std::cout << "No order without debtrel found in database." << std::endl;
        throw;
    }

    CremaDataSearchValues order;
    order.orderno = result.getInt32("kdauftragnr");
    order.branchno = result.getInt16("vertriebszentrumnr");
    return order;
}

void MocFinishedTodayCremaOrder::createDebtRelEntry(const int orderno)
{
    std::stringstream ss;
    ss << "INSERT INTO kdauftragdebtrel (kdauftragnr, relreason, relcomment, reluser, isreleased, relcounter, approvalcounter, cancelcounter, debtlimit, useddebtlimit, ordervalue) "
        << "VALUES(" << orderno << " , 'Zahlung ist unterwegs', 'OK', 'Test.Buddy', 1, 1, 1, 0, 41740.74, 41362.21, 969.51);";

    _session.doSQL(ss.str());
}
