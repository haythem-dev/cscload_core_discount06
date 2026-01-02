#include "MocTour.h"
#include "SessionUtil.h"
#include <sstream>

MocTour::MocTour(SessionUtil& session) : _session(session)
{
    cleanup();
}

MocTour::~MocTour()
{
    // Teardown: Clean up resources
    cleanup();
}

short MocTour::getBranchNo() const
{
    return branchno;
}

void MocTour::setup(long customerno)
{
    _session.doSQL(createInsertRechnerStmt());

    _session.doSQL(createInsertKundeStmt(customerno));
    _session.doSQL(createInsertKundeschalterStmt(customerno));
    _session.doSQL(createInsertTourplantagStmt(customerno, "140206", ""));
    _session.doSQL(createInsertTourplantagStmt(customerno, "160206", "SO"));
    _session.doSQL(createInsertTourStmt("140206"));
    _session.doSQL(createInsertTourStmt("160206"));
    _session.doSQL(createInsertTourplantagwocheStmt(customerno, "103526"));
    _session.doSQL(createInsertTourplanwocheStmt("103526"));
}

std::string MocTour::createInsertRechnerStmt() const
{
    std::stringstream ss;
    ss << "INSERT INTO rechner (filialnr, rechner_name, standort, pflege, datenbank_name, szentral, warehouse_datenbankname, inbound_datenbankname) "
       << "VALUES(" << branchno << ", 'zdev21', 'TESTBURG', '0', 'ode21@" << _session.getDatabaseServer() << "', '1', 'wde21@" << _session.getDatabaseServer()
       <<         "', 'ide21@" << _session.getDatabaseServer() << "')";
    return ss.str();
}

std::string MocTour::createInsertKundeStmt(long customerno) const
{
    std::stringstream ss;
    ss << "INSERT INTO kunde (idfnr, matchcode, filialnr, kdnr, etartklasse1, etartklasse2, etkdmerkmal1, etkdmerkmal2, anredekz, nameapo, nameinhaber, "
       << "  strasse, ort, postleitzahl, telnr, telnrdafue, faxnr, telkurzwahl, imsbezirknr, kdgruppe, personalnrvertr, dafuesystem, kzkddoppelkontr, lagerfachnrrgbei, "
       << "  anzposls_rg, anzpossortbehaelt, kzkdklasse, originalfilialnr, notfilialnr, bemerkungen, kundetext, verbundkunde, stdaufkobuart, password, kuehlbox, "
       << "  tourenkippzeit, kzupd, vzkk1, ims3000, land, druckreimportliste, prismadiskette, azyxkreisnr, pharmakreisnr, umsatzsteuerid, imsaponr, imskundenart, "
       << "  vertriebszentrumnr, kundennr, bundesland, tm_date, tm_time, loginid, changeid, emailadresse, pooltyp, poolnr, nachliefertyp, partnernr, kzsprache, "
       << "  phonepriority, kzpsychostoffe, softwarehouse, xmlpreislevel, prewholetyp, xmlinfolevel, nationalcustomerno, ratiocustomerno, anzaufclose, payment_term, "
       << "  krankenkassennr, calculationtype, apolizens, btmlizens, surcharge_basic, deduction_basic, surchargepct, deductionpct, vatregistered, rebatemethfreesale, "
       << "  rebatemethhealthf, maincstno, mastercstno, surcharge_basic_kk, deduction_basic_kk, surchargepctkk, deductionpctkk, kundeean, liefermeldung, manufacturerno, "
       << "  msv3cfgchangedate, minlogaddbehavior, packagefee, sendcollectivinvoice, linefee) "
       << "VALUES (" << customerno << ", 'AESCULAP BRE', " << branchno << ", 3340433, 65529, 0, 65529, 36864, 1, 'AESCULAP-APOTHEKE', 'CHRISTOPH BANNERT', "
       << "  'GERHARD-ROHLFS-STR. 16A', 'BREMEN', '28757', '0421669650', '', '04216696540', '', 9031211, '01', 78, '05', '0', '', 0, 0, 'C', 0, 0, 'AWINTA PROKAS', "
       << "  '', '1', '', '', '1', 0, '1', '0', 1031211, 'D', '4', '1', 107781, 401129, '', '', '0', " << branchno << ", " << customerno << ", 'HB', 20251006, "
       << "  191457, 1, 'I', 'INFO@AESCULAP-APOTHEKE.COM', 0, 0, '6', 330019063, 'DE', 'C', '1', 'AWI', '0', 'N', '2', '0000000', '', 0, 'GF10', '000000', '0', "
       << "  '', '', 0, 0, 0.00, 0.00, 0, 1, 0, 0, " << customerno << ", 0, 0, 0.00, 0.00, '            0', 0, 0, 0, '0', 0.00, '', 0.00);";
    return ss.str();
}

std::string MocTour::createInsertKundeschalterStmt(long customerno) const
{
    std::stringstream ss;
    ss << "INSERT INTO kundeschalter (idfnr, skdwerbefachbelegt, skdkdfachaktiv, skdnatrarestakzept, skdnettoaktion, skdetikettservice, skddefektliefern, "
       << "  skddefektabsagen, skdsammldafue, skdapoekstatisitik, skdautoerhoehgnnnr, skddefektmeldgausw, skdkontrkobelege, skdauftragzusammen, skdmwsthalb, "
       << "  skdstadtkunde, skdvalutasperre, skdschwerpunkt1, skdschwerpunkt2, skdschwerpunkt3, skdschwerpunkt4, skdschwerpunkt5, skdverbundganz, skdabschlagrechn, "
       << "  skdkdkritisch, skdeilsperre, skdabsagen, skdvipkunde, skdauftragsplit, skdmusskopf, skdsepauft, skdauftragzurueck, skdbestzeit, skdwirdbearb, kzupd, "
       << "  skdreimport, skdwarenachliefern, skdpinkunde, skdadgkunde, skddruckbetapharm, skdfax400, skdkundeaegesperrt, skddrucketikett, skddrucktierarznei, "
       << "  skddruckkaufstrukt, skdkaufstruktart, skdmonatsrabatt, skddruckumsatz, vertriebszentrumnr, kundennr, tm_date, tm_time, loginid, changeid, skdanrufgenerell, "
       << "  skdblickpunktabo, skdbuecher, skdvertriebbindung, skdpool, skdbouhon, skdroche, skdvichy, skdvbfilialemeld, skdrrabschluss, skdabschlusseil, skdtrennalphatext, "
       << "  skdrr0800, skdtrennalphaurr, skdoriginalmeld, skdmidas, skdmehrfachbestell, skdomgkunde, skdcharge, skdkeinnl, skdtrenndefekt, skdversandapo, skdnoclosedefvb, "
       << "  skdparternariat, skdbaauftrag, skdcheckdouble, skdnosub, skdwatchorder, skdretailpermit, skdhalfmargin, skddiscountexcept, skdliste5, skdinvoicedisc, "
       << "  skdinvoiceemail, skdnoexpiryinfo, medprod_abg_verord, skdnoshortreport, skdgiveprodquota, skdavoiddefectclearing, smsv3dayibtinfo, skdpseudoidfnr_uw, "
       << "  msv3noordercons, noorderconsaftermot, skdmailinvoice, skdmailbatchchangeadvice, skdfaxinvoice, skdfaxbatchchangeadvice, skdfmd, skdrxa, skdtournee) "
       << "VALUES (" << customerno << ", '1', '0', '0', '1', '', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', "
       << "  '', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '2', '1', '0', '1', '1', '1', '1', '0', '0', " << branchno << ", " << customerno << ", "
       << "  20251006, 191457, 1, 'I', '0', '0', '1', '1', '0', '0', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', "
       << "  '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'H', '');";
    return ss.str();
}

std::string MocTour::createInsertTourplantagStmt(long customerno, std::string tourid, std::string ordertype) const
{
    std::stringstream ss;
    ss << "INSERT INTO tourplantag (idfnr, datumkommi, tourid, reihenfolgenr, fahrtzeit, bemerkungen, kzupd, istverbundtour, vertriebszentrumnr, kundennr, "
       << "  tm_date, tm_time, loginid, changeid, koart, tourinaktiv, kippzeit, kzautozuord, istvatour, kdauftragart, deliverbranchno, sencloserdone, sisshuttletour, "
       << "  orderlabelcount, checktimetotour, scheckorder, isbtm, iskk, isk08, isk20, returnstour, transpexclpsycho, transpexclcooled, transpexclexpensive, checkpositions, "
       << "  checkremark, plannedcall, loadingprocid) "
       << "VALUES (" << customerno << ", " << TourUtil::getCurrentDate().GetYYYYMMDD() << ", '" << tourid << "', 150, 188, '', '1', '0', " << branchno << ", " << customerno << ", "
       << "  " << TourUtil::getCurrentDate().GetYYYYMMDD() << ", 192029, 1, 'U', '', '0', 61, '1', '0', '" << ordertype << "', 0, '', '', 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, "
       << "  0, '', 0, '');";
    return ss.str();
}

std::string MocTour::createInsertTourStmt(std::string tourid) const
{
    std::stringstream ss;
    ss << "INSERT INTO tour (datumkommi, tourid, zeitkoende, datumversand, zeitversand, bahnhofversand, tourstat, druckstat, vorabscheindrucken, "
       << "  tourmitverbund, fahrtzeit, tourstrecke, bezeichnung, bemerkungen, druckfachnr, lagrechtour, kzupd, filialnr, kdauftragart, tourinaktiv, ersatzfilialnr, "
       << "  kippzeit, checktimetotour, scheckorder, karenzzeit, snighttour, loadingprocid) "
       << "VALUES (" << TourUtil::getCurrentDate().GetYYYYMMDD() << ", '" << tourid << "', 104400, " << TourUtil::getCurrentDate().GetYYYYMMDD() << ", 104400, 1, '0', "
       << "  '', '0', '', 0, 0, 'V HASTEDT SA.', 'D HB FF KIYMAZ', 0, 0, '1', " << branchno << ", '', '', 0, 0, 0, 0, 0, 0, '');";
    return ss.str();
}

std::string MocTour::createInsertTourplantagwocheStmt(long customerno, std::string tourid) const
{
    std::stringstream ss;
    ss << "INSERT INTO tourplantagwoche (vertriebszentrumnr, kundennr, tourid, tagestyp, kzupd, weekday, istverbundtour, kdauftragart, fahrtzeit, isbtm, iskk, "
       << "  isk08, isk20, returnstour, kippzeit, reihenfolgenr, transpexclpsycho, transpexclcooled, transpexclexpensive, checkpositions, checkremark, plannedcall, "
       << "  kzautozuord, scheckorder, checktimetotour, bemerkungen, loadingprocid) "
       << "VALUES (" << branchno << ", " << customerno << ", '" << tourid << "', 'MO', '1', 1, '1', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, '0', 0, 0, '', '');";
    return ss.str();
}

std::string MocTour::createInsertTourplanwocheStmt(std::string tourid) const
{
    std::stringstream ss;
    ss << "INSERT INTO tourplanwoche (tourid, tagestyp, kzupd, filialnr, weekday, lagrechtour, karenzzeit, kippzeit, invalidfromdate, invalidtodate, loadingprocid) "
       << "VALUES ('" << tourid << "', 'MO', '1', " << branchno << ", 1, 0, 0, 0, 0, 0, '             ');";
    return ss.str();
}

void MocTour::cleanup()
{
    std::stringstream ssRechner;
    ssRechner << "DELETE FROM rechner WHERE filialnr = " << branchno << ";";
    _session.doSQL(ssRechner.str());
    std::stringstream ssKunde;
    ssKunde << "DELETE FROM kunde WHERE filialnr = " << branchno << ";";
    _session.doSQL(ssKunde.str());
    std::stringstream ssKundeschalter;
    ssKundeschalter << "DELETE FROM kundeschalter WHERE vertriebszentrumnr = " << branchno << ";";
    _session.doSQL(ssKundeschalter.str());
    std::stringstream ssTourplantag;
    ssTourplantag << "DELETE FROM tourplantag WHERE vertriebszentrumnr = " << branchno << ";";
    _session.doSQL(ssTourplantag.str());
    std::stringstream ssTour;
    ssTour << "DELETE FROM tour WHERE filialnr = " << branchno << ";";
    _session.doSQL(ssTour.str());
    std::stringstream ssTourplantagwoche;
    ssTourplantagwoche << "DELETE FROM tourplantagwoche WHERE vertriebszentrumnr = " << branchno << ";";
    _session.doSQL(ssTourplantagwoche.str());
    std::stringstream ssTourplanwoche;
    ssTourplanwoche << "DELETE FROM tourplanwoche WHERE filialnr = " << branchno << ";";
    _session.doSQL(ssTourplanwoche.str());
}
