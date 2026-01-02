// ae.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ppDataTypes.h"
#include <encoding.h>
#include <converttypes.h>

#include "MainFrm.h"
#include "AeDoc.h"
#include "AeFView.h"
#include "AeView.h"
#include "DBenKen.h"
#include "DKndWahl.h"
#include "DAufEnd.h"
#include "DOffAuftr.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "DArtInf.h"
#include "DAufInf.h"
#include "SplashWnd.h"
#include "DParAufArt.h"
#include "DParBuchArt.h"
#include "DParKomArt.h"
#include "DAnzAeUser.h"
#include "DParKaBaKomb.h"
#include "DParKondGrp.h"
#include "DBenKennAend.h"
#include "DCheckOpenCallOrOrder.h"
#include "DParAufBearb.h"
#include "DParAufBearbErg.h"
#include "DParNachart.h"
#include "DParKoBehTyp.h"
#include "DBenVwtng.h"
#include "WeLaEk.h"
#include "DInfoListe.h"
#include "DInfoUpdZ.h"
#include "DPlanTag.h"
#include "DAutrStat.h"
#include "DTourAusw.h"
#include "DZeitart.h"
#include "DSeralog.h"
#include "Entsperr.h"
#include "DUpdNachl.h"
#include "DProtNachLief.h"
#include "AeKndNachl.h"
#include <callback.h>
#include "DAeStatusAe.h"
#include "GetNextPhoneCall.h"
#include "AltFil.h"
#include <filinf.h>
#include "DPlanAbweichung.h"
#include "DParAuftrendzeit.h"
#include "DAuftragartKd.h"
#include "DUpdPartner.h"
#include "DAttachPartner.h"
#include "DFilialpartner.h"
#include <modemtab.h>
#include "DRrUnlock.h"
//Anrufplan
#include "ppCustomerCallPlanDay.h" //because we use dynamic sql, and only once shoud start the prepare statement
#include "ppCustomerDisplay.h"
#include "ppCallPlanParameter.h"
#include "CDeleteReservation.h"
#include "CPCallPlanMaintenance.h"
#include "CPCallPlanLoadListe.h"
#include "CPCallPlanUndertake.h"
#include "CPCustomerTelNo.h"
#include "CPCustomerProperties.h"
#include "CPRegionMaintenance.h"
#include "DChooseFiliale.h"
#include "druckpara.h"
#include "NMDProgress.h"
#include "PLocalOptions.h"
#include <customer.h>
#include "DAeNotdienst.h"
#include "DLagerrevision.h"
#include "DArtikelkonto.h"
#include <touren.h>
#include "DSonderTouren.h"
#include "ProCenter.h"
#include "DHPLogon.h"
#include "DHPMakeCall.h"
#include <controlling.h>
#include <artikel.h>
#include "DStockEntry.h"
#include "DCustomerRouting.h"
#include "DBackRouting.h"
#include "DRoutBack.h"
#include "DCustomerOrderCheck.h"
#include "DDealerUmsatz.h"
#include "DUpdDivision.h"
#include "DIbtBranches.h"
#include "DAufAuswahl.h"
#include "FCOrders.h"
#include "DCSVFormat.h"
#include "AboutDlg.h"
#include <boost/make_shared.hpp>
#include "OrderTypeModel.h"
#include "AeAppModel.h"
#include "CallbackStatusManager.h"

#include "aeconnection.h"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>



/////////////////////////////////////////////////////////////////////////////
// CAeApp

BEGIN_MESSAGE_MAP(CAeApp, CWinAppMultiLang)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(ID_KUNDE_KND_WAHL, OnKundeKndWahl)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_KND_WAHL, OnUpdateKundeKndWahl)
    ON_COMMAND(ID_INF_KUNDE, OnInfKunde)
    ON_UPDATE_COMMAND_UI(ID_INF_KUNDE, OnUpdateInfKunde)
    ON_UPDATE_COMMAND_UI(ID_INF_ART, OnUpdateInfArt)
    ON_COMMAND(ID_INF_AUF, OnInfAuf)
    ON_UPDATE_COMMAND_UI(ID_INF_AUF, OnUpdateInfAuf)
    ON_COMMAND(ID_KUNDE_KUNDE_AUS_PLAN, OnKundeKundeAusPlan)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_KUNDE_AUS_PLAN, OnUpdateKundeKundeAusPlan)
    ON_UPDATE_COMMAND_UI(ID_KUNDE_OFFENE_AUFTRGE, OnUpdateKundeOffeneAuftrge)
    ON_COMMAND(ID_KUNDE_OFFENE_AUFTRGE, OnKundeOffeneAuftrge)
    ON_COMMAND(ID_INF_ART, OnInfArt)
    ON_COMMAND(ID_KOMB_AUFT_BUCH_ART, OnKombAuftBuchArt)
    ON_UPDATE_COMMAND_UI(ID_KOMB_AUFT_BUCH_ART, OnUpdateKombAuftBuchArt)
    ON_COMMAND(ID_DEF_BUCHART, OnDefBuchart)
    ON_UPDATE_COMMAND_UI(ID_DEF_BUCHART, OnUpdateDefBuchart)
    ON_COMMAND(ID_DEF_KOMMIARTEN, OnDefKommiarten)
    ON_UPDATE_COMMAND_UI(ID_DEF_KOMMIARTEN, OnUpdateDefKommiarten)
    ON_COMMAND(ID_DEF_KONDGRP, OnDefKondgrp)
    ON_UPDATE_COMMAND_UI(ID_DEF_KONDGRP, OnUpdateDefKondgrp)
    ON_COMMAND(ID_DEF_AUFTRART, OnDefAuftrart)
    ON_UPDATE_COMMAND_UI(ID_DEF_AUFTRART, OnUpdateDefAuftrart)
    ON_COMMAND(ID_PAR_AUFBEARB, OnParAufbearb)
    ON_UPDATE_COMMAND_UI(ID_PAR_AUFBEARB, OnUpdateParAufbearb)
    ON_COMMAND(ID_PAR_AUFBEARBERG, OnParAufbearberg)
    ON_UPDATE_COMMAND_UI(ID_PAR_AUFBEARBERG, OnUpdateParAufbearberg)
    ON_COMMAND(ID_PAR_KOBEHTYP, OnParKobehtyp)
    ON_UPDATE_COMMAND_UI(ID_PAR_KOBEHTYP, OnUpdateParKobehtyp)
    ON_COMMAND(ID_PAR_KOMMI, OnParKommi)
    ON_UPDATE_COMMAND_UI(ID_PAR_KOMMI, OnUpdateParKommi)
    ON_COMMAND(ID_PAR_NACHRART, OnParNachrart)
    ON_UPDATE_COMMAND_UI(ID_PAR_NACHRART, OnUpdateParNachrart)
    ON_COMMAND(ID_HILSPROG_KENNWORT, OnHilsprogKennwort)
    ON_UPDATE_COMMAND_UI(ID_HILSPROG_KENNWORT, OnUpdateHilsprogKennwort)
    ON_COMMAND(ID_HILFSPR_TASCHENRECHNER, OnHilfsprTaschenrechner)
    ON_UPDATE_COMMAND_UI(ID_HILFSPR_TASCHENRECHNER, OnUpdateHilfsprTaschenrechner)
    ON_COMMAND(ID_HILFSPROGRAMME_BENVERW, OnHilfsprogrammeBenverw)
    ON_UPDATE_COMMAND_UI(ID_HILFSPROGRAMME_BENVERW, OnUpdateHilfsprogrammeBenverw)
    ON_COMMAND(ID_FAST_OPEN_ORDER, OnFastOpenOrder)
    ON_UPDATE_COMMAND_UI(ID_FAST_OPEN_ORDER, OnUpdateFastOpenOrder)
    ON_COMMAND(ID_SORTZURORDER_AUFTRAGSNR, OnSortzurorderAuftragsnr)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_AUFTRAGSNR, OnUpdateSortzurorderAuftragsnr)
    ON_COMMAND(ID_SORTZURORDER_APOSCHLZ, OnSortzurorderAposchlz)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_APOSCHLZ, OnUpdateSortzurorderAposchlz)
    ON_COMMAND(ID_SORTZURORDER_IDF, OnSortzurorderIdf)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_IDF, OnUpdateSortzurorderIdf)
    ON_COMMAND(ID_SORTZURORDER_TOUR, OnSortzurorderTour)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_TOUR, OnUpdateSortzurorderTour)
    ON_COMMAND(ID_EXTRAS_ANRUFPLANZUERSTABARBEITEN, OnExtrasAnrufplanzuerstabarbeiten)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_ANRUFPLANZUERSTABARBEITEN, OnUpdateExtrasAnrufplanzuerstabarbeiten)
    ON_COMMAND(ID_AUFTRAG_DAFZURCKGESTELLTEAUFTRGE, OnAuftragDafzurckgestellteauftrge)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_DAFZURCKGESTELLTEAUFTRGE, OnUpdateAuftragDafzurckgestellteauftrge)
    ON_COMMAND(ID_INFORMATIONEN_INFOLISTE, OnInformationenInfoliste)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_INFOLISTE, OnUpdateInformationenInfoliste)
    ON_COMMAND(ID_INFORMATIONEN_STATUSAUFTRAGSVERARBEITUNG, OnInformationenStatusauftragsverarbeitung)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_STATUSAUFTRAGSVERARBEITUNG, OnUpdateInformationenStatusauftragsverarbeitung)
    ON_COMMAND(ID_AUFTRAG_STATISTIK, OnAuftragStatistik)
    ON_COMMAND(ID_INFORMATIONEN_TOUREN, OnInformationenTouren)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_TOUREN, OnUpdateInformationenTouren)
    ON_COMMAND(ID_INFORMATIONEN_TAGESANRUFPLAN, OnInformationenTagesanrufplan)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_TAGESANRUFPLAN, OnUpdateInformationenTagesanrufplan)
    ON_COMMAND(ID_INFO_UPD, OnInfoUpd)
    ON_UPDATE_COMMAND_UI(ID_INFO_UPD, OnUpdateInfoUpd)
    ON_COMMAND(ID_ALTFIL_UPD, OnAltfilUpd)
    ON_UPDATE_COMMAND_UI(ID_ALTFIL_UPD, OnUpdateAltfilUpd)
    ON_COMMAND(ID_ZEITART_UPD, OnZeitartUpd)
    ON_UPDATE_COMMAND_UI(ID_ZEITART_UPD, OnUpdateZeitartUpd)
    ON_COMMAND(ID_INFORMATIONEN_SERALOG, OnInformationenSeralog)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_SERALOG, OnUpdateInformationenSeralog)
    ON_COMMAND(ID_EXTRAS_KEINEPARAANRUFE, OnExtrasKeineparaanrufe)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_KEINEPARAANRUFE, OnUpdateExtrasKeineparaanrufe)
    ON_COMMAND(ID_AE_AUFTR_ENTSP, OnAeAuftrEntsp)
    ON_UPDATE_COMMAND_UI(ID_AE_AUFTR_ENTSP, OnUpdateAeAuftrEntsp)
    ON_COMMAND(ID_BEARBEITEN_NACHLIEFERPOSITIONEN, OnBearbeitenNachlieferpositionen)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_NACHLIEFERPOSITIONEN, OnUpdateBearbeitenNachlieferpositionen)
    ON_COMMAND(ID_AUFTRAG_FFNENPARAAUFTRAG, OnAuftragFfnenparaauftrag)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_FFNENPARAAUFTRAG, OnUpdateAuftragFfnenparaauftrag)
    ON_COMMAND(ID_VERWALTUNG_ANZEIGEBENUTZERLISTE, OnVerwaltungAnzeigebenutzerliste)
    ON_UPDATE_COMMAND_UI(ID_VERWALTUNG_ANZEIGEBENUTZERLISTE, OnUpdateVerwaltungAnzeigebenutzerliste)
    ON_COMMAND(ID_VERWALTUNG_RUFZEITENABWEICHUNGENDEFINIEREN, OnVerwaltungRufzeitenabweichungendefinieren)
    ON_UPDATE_COMMAND_UI(ID_VERWALTUNG_RUFZEITENABWEICHUNGENDEFINIEREN, OnUpdateVerwaltungRufzeitenabweichungendefinieren)
    ON_COMMAND(ID_BEARBEITEN_LAGERENDKONTROLLE, OnBearbeitenLagerendkontrolle)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_LAGERENDKONTROLLE, OnUpdateBearbeitenLagerendkontrolle)
    ON_COMMAND(ID_BEARBEITEN_NACHLIEFERPOSITIONEN_KND, OnBearbeitenNachlieferpositionenKnd)
    ON_UPDATE_COMMAND_UI(ID_BEARBEITEN_NACHLIEFERPOSITIONEN_KND, OnUpdateBearbeitenNachlieferpositionenKnd)
    ON_COMMAND(ID_PROT_NACHLIFBEARB, OnProtNachlifbearb)
    ON_UPDATE_COMMAND_UI(ID_PROT_NACHLIFBEARB, OnUpdateProtNachlifbearb)
    ON_COMMAND(ID_PAR_AUFTRENDZEIT, OnParAuftrendzeit)
    ON_UPDATE_COMMAND_UI(ID_PAR_AUFTRENDZEIT, OnUpdateParAuftrendzeit)
    ON_COMMAND(ID_KND_AUFTRAGART, OnKndAuftragart)
    ON_UPDATE_COMMAND_UI(ID_KND_AUFTRAGART, OnUpdateKndAuftragart)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_STATISTIK, OnUpdateAuftragStatistik)
    ON_COMMAND(ID_EXTRAS_KUNDE_IDF, OnExtrasKundeIdf)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_KUNDE_IDF, OnUpdateExtrasKundeIdf)
    ON_COMMAND(ID_EXTRAS_PZN_DIREKT, OnExtrasPznDirekt)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_PZN_DIREKT, OnUpdateExtrasPznDirekt)
    ON_COMMAND(ID_VERWALTUNG_CALLBACK, OnVerwaltungCallback)
    ON_UPDATE_COMMAND_UI(ID_VERWALTUNG_CALLBACK, OnUpdateVerwaltungCallback)
    ON_COMMAND(ID_EXTRAS_ATTACH_PARTNER, OnExtrasAttachPartner)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_ATTACH_PARTNER, OnUpdateExtrasAttachPartner)
    ON_COMMAND(ID_VERWALTUNG_FILIALPARTNER, OnVerwaltungFilialpartner)
    ON_UPDATE_COMMAND_UI(ID_VERWALTUNG_FILIALPARTNER, OnUpdateVerwaltungFilialpartner)
    ON_COMMAND(ID_EXTRAS_RR_MELD, OnExtrasRrMeld)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_RR_MELD, OnUpdateExtrasRrMeld)
    ON_COMMAND(ID_AE_RR_ENTSP, OnAeRrEntsp)
    ON_UPDATE_COMMAND_UI(ID_AE_RR_ENTSP, OnUpdateAeRrEntsp)
    ON_COMMAND(ID_EXTRAS_RR_NOT_DONE, OnExtrasRrNotDone)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_RR_NOT_DONE, OnUpdateExtrasRrNotDone)
    ON_COMMAND(ID_EXTRAS_NO_BEEP, OnExtrasNoBeep)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NO_BEEP, OnUpdateExtrasNoBeep)
    ON_COMMAND(ID_ANRUFPLAN_MASTERPLAN_PFLEGE, OnAnrufplanMasterplanPflege)
    ON_UPDATE_COMMAND_UI(ID_ANRUFPLAN_MASTERPLAN_PFLEGE, OnUpdateAnrufplanMasterplanPflege)
    ON_COMMAND(ID_RUFADMIN_ABWEICHUNG, OnRufadminAbweichung)
    ON_UPDATE_COMMAND_UI(ID_RUFADMIN_ABWEICHUNG, OnUpdateRufadminAbweichung)
    ON_COMMAND(ID_RUFADMIN_UEBERNAHME, OnRufadminUebernahme)
    ON_UPDATE_COMMAND_UI(ID_RUFADMIN_UEBERNAHME, OnUpdateRufadminUebernahme)
    ON_COMMAND(ID_ANRUFPLANVERWALTUNG_REGIONENFESTLEGEN, OnAnrufplanverwaltungRegionenfestlegen)
    ON_UPDATE_COMMAND_UI(ID_ANRUFPLANVERWALTUNG_REGIONENFESTLEGEN, OnUpdateAnrufplanverwaltungRegionenfestlegen)
    ON_COMMAND(ID_AUSWERT_MASTER, OnAuswertMaster)
    ON_UPDATE_COMMAND_UI(ID_AUSWERT_MASTER, OnUpdateAuswertMaster)
    ON_COMMAND(ID_ANRUFPLANVERWALTUNG_LOKALEEINSTELLUNGEN, OnAnrufplanverwaltungLokaleeinstellungen)
    ON_UPDATE_COMMAND_UI(ID_ANRUFPLANVERWALTUNG_LOKALEEINSTELLUNGEN, OnUpdateAnrufplanverwaltungLokaleeinstellungen)
    ON_COMMAND(ID_ANRUFPLANVERWALTUNG_KUNDENDATEN_DAFENUMMERNDERN, OnAnrufplanverwaltungKundendatenDafenummerndern)
    ON_UPDATE_COMMAND_UI(ID_ANRUFPLANVERWALTUNG_KUNDENDATEN_DAFENUMMERNDERN, OnUpdateAnrufplanverwaltungKundendatenDafenummerndern)
    ON_COMMAND(ID_ANRUFPLANVERWALTUNG_KUNDENDATEN_KUNDENEIGENSCHAFTEN, OnAnrufplanverwaltungKundendatenKundeneigenschaften)
    ON_UPDATE_COMMAND_UI(ID_ANRUFPLANVERWALTUNG_KUNDENDATEN_KUNDENEIGENSCHAFTEN, OnUpdateAnrufplanverwaltungKundendatenKundeneigenschaften)
    ON_COMMAND(ID_INFORMATIONEN_NOTDIENST, OnInformationenNotdienst)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_NOTDIENST, OnUpdateInformationenNotdienst)
    ON_COMMAND(ID_EXTRAS_POS_ZUSAMMEN, OnExtrasPosZusammen)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_POS_ZUSAMMEN, OnUpdateExtrasPosZusammen)
    ON_COMMAND(ID_EXTRAS_NICHT_MELD_AUFTRAG_OFFEN, OnExtrasNichtMeldAuftragOffen)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NICHT_MELD_AUFTRAG_OFFEN, OnUpdateExtrasNichtMeldAuftragOffen)
    ON_COMMAND(ID_INFORMATIONEN_LAGERREVISION, OnInformationenLagerrevision)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_LAGERREVISION, OnUpdateInformationenLagerrevision)
    ON_COMMAND(ID_INFORMATIONEN_ARTIKELKONTO, OnInformationenArtikelkonto)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_ARTIKELKONTO, OnUpdateInformationenArtikelkonto)
    ON_COMMAND(ID_EXTRAS_AUSWAHL_KURZ, OnExtrasAuswahlKurz)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_AUSWAHL_KURZ, OnUpdateExtrasAuswahlKurz)
    ON_COMMAND(ID_EXTRAS_ANZEIGE_ALLE_POS, OnExtrasAnzeigeAllePos)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_ANZEIGE_ALLE_POS, OnUpdateExtrasAnzeigeAllePos)
    ON_COMMAND(ID_SORTZURORDER_AART, OnSortzurorderAart)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_AART, OnUpdateSortzurorderAart)
    ON_COMMAND(ID_EXTRAS_ANZEIGE_ALLE_DEF, OnExtrasAnzeigeAlleDef)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_ANZEIGE_ALLE_DEF, OnUpdateExtrasAnzeigeAlleDef)
    ON_COMMAND(ID_EXTRAS_VERARB_REGIO, OnExtrasVerarbRegio)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_VERARB_REGIO, OnUpdateExtrasVerarbRegio)
    ON_COMMAND(ID_PFLEGE_SONDER_TOUREN, OnPflegeSonderTouren)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_SONDER_TOUREN, OnUpdatePflegeSonderTouren)
    ON_COMMAND(ID_MAIL_VZ, OnMailVz)
    ON_UPDATE_COMMAND_UI(ID_MAIL_VZ, OnUpdateMailVz)
    ON_COMMAND(ID_EXTRAS_SOFORT, OnExtrasSofort)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_SOFORT, OnUpdateExtrasSofort)
    ON_COMMAND(ID_HIPATH_LOGOFF, OnHipathLogoff)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_LOGOFF, OnUpdateHipathLogoff)
    ON_COMMAND(ID_HIPATH_LOGON, OnHipathLogon)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_LOGON, OnUpdateHipathLogon)
    ON_COMMAND(ID_HIPATH_PAUSE_START, OnHipathPauseStart)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_PAUSE_START, OnUpdateHipathPauseStart)
    ON_COMMAND(ID_HIPATH_PAUSE_STOP, OnHipathPauseStop)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_PAUSE_STOP, OnUpdateHipathPauseStop)
    ON_COMMAND(ID_HIPATH_CALL, OnHipathCall)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_CALL, OnUpdateHipathCall)
    ON_COMMAND(ID_HIPATH_CALL_END, OnHipathCallEnd)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_CALL_END, OnUpdateHipathCallEnd)
    ON_COMMAND(ID_INFO_UPD_ZENT, OnInfoUpdZent)
    ON_UPDATE_COMMAND_UI(ID_INFO_UPD_ZENT, OnUpdateInfoUpdZent)
    ON_COMMAND(IDD_AE_PAR_CUSTOMER_ORDER_CHECK, OnKundeAuftragseingangsPruefung)
    ON_UPDATE_COMMAND_UI(IDD_AE_PAR_CUSTOMER_ORDER_CHECK, OnUpdateKundeAuftragseingangsPruefung)
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinAppMultiLang::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinAppMultiLang::OnFileOpen)
    // Standard print setup command
    ON_COMMAND(ID_FILE_PRINT_SETUP, CWinAppMultiLang::OnFilePrintSetup)
    ON_COMMAND(ID_EXTRAS_MATCHCODE, OnExtrasMatchcode)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_MATCHCODE, OnUpdateExtrasMatchcode)
    ON_COMMAND(ID_PFLEGE_KUNDENRUFWEITERLEITUNGPFLEGEN, OnPflegeKundenrufweiterleitungpflegen)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_KUNDENRUFWEITERLEITUNGPFLEGEN, OnUpdatePflegeKundenrufweiterleitungpflegen)
    ON_COMMAND(ID_HIPATH_TRACE, OnHipathTrace)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_TRACE, OnUpdateHipathTrace)
    ON_COMMAND(ID_INFORMATIONEN_STOCKENTRY, OnInformationenStockentry)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_STOCKENTRY, OnUpdateInformationenStockentry)
    ON_COMMAND(ID_HIPATH_DEL, OnHipathDel)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_DEL, OnUpdateHipathDel)
    ON_COMMAND(ID_PFLEGE_BACKROUTING, OnPflegeBackrouting)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_BACKROUTING, OnUpdatePflegeBackrouting)
    ON_COMMAND(ID_HIPATH_ROUTBACK, OnHipathRoutback)
    ON_UPDATE_COMMAND_UI(ID_HIPATH_ROUTBACK, OnUpdateHipathRoutback)
    ON_COMMAND(ID_EXTRAS_NUREIGENERUFE, OnExtrasNureigenerufe)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NUREIGENERUFE, OnUpdateExtrasNureigenerufe)
    ON_COMMAND(ID_SORTZURORDER_KDKLASSE, OnSortzurorderKdklasse)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_KDKLASSE, OnUpdateSortzurorderKdklasse)
    ON_COMMAND(ID_SORTZURORDER_POS, OnSortzurorderPos)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_POS, OnUpdateSortzurorderPos)
    ON_COMMAND(ID_SORTZURORDER_BRANCHNO, OnSortzurorderBranchno)
    ON_UPDATE_COMMAND_UI(ID_SORTZURORDER_BRANCHNO, OnUpdateSortzurorderBranchno)
    ON_COMMAND(ID_EXTRAS_RABATT, OnExtrasRabatt)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_RABATT, OnUpdateExtrasRabatt)
    ON_COMMAND(ID_EXTRAS_UEBERGEHENVA10, OnExtrasUebergehenva10)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_UEBERGEHENVA10, OnUpdateExtrasUebergehenva10)
    ON_COMMAND(ID_INFORMATIONEN_DEALERUMSATZ, OnInformationenDealerUmsatz)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_DEALERUMSATZ, OnUpdateInformationenDealerUmsatz)
    ON_COMMAND(ID_EXTRAS_NURAKTIVEARTIKELINF11, OnExtrasNuraktiveartikelinf11)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NURAKTIVEARTIKELINF11, OnUpdateExtrasNuraktiveartikelinf11)
    ON_COMMAND(ID_EXTRAS_NOBATCH, OnExtrasNobatch)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NOBATCH, OnUpdateExtrasNobatch)
    ON_COMMAND(ID_EXTRAS_NO_PROMO, OnExtrasNoPromo)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NO_PROMO, OnUpdateExtrasNoPromo)
    ON_COMMAND(ID_EXTRAS_NO_KIPPZEIT, OnExtrasNoKippzeit)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_NO_KIPPZEIT, OnUpdateExtrasNoKippzeit)
    ON_COMMAND(ID_IBTBRANCH_UPD, &CAeApp::OnIbtbranchUpd)
    ON_UPDATE_COMMAND_UI(ID_IBTBRANCH_UPD, &CAeApp::OnUpdateIbtbranchUpd)
    ON_COMMAND(ID_EXTRAS_INFOLISTE_FIRSTLETTER, &CAeApp::OnExtrasInfolisteFirstletter)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_INFOLISTE_FIRSTLETTER, &CAeApp::OnUpdateExtrasInfolisteFirstletter)
    ON_COMMAND(ID_AUFTRAG_FC_ORDERS, &CAeApp::OnAuftragFcOrders)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_FC_ORDERS, &CAeApp::OnUpdateAuftragFcOrders)
    ON_COMMAND(ID_EXTRAS_KOMMA_NO_TAB, &CAeApp::OnExtrasKommaNoTab)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_KOMMA_NO_TAB, &CAeApp::OnUpdateExtrasKommaNoTab)
    ON_COMMAND(ID_PFLEGE_CSVIMPORTPARAM, &CAeApp::OnPflegeCsvimportparam)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_CSVIMPORTPARAM, &CAeApp::OnUpdatePflegeCsvimportparam)
    ON_COMMAND(ID_PFLEGE_DELETERESERVATIONS, &CAeApp::OnDeleteReservation)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_DELETERESERVATIONS, &CAeApp::OnUpdatePflegeDeleteReservation)
    END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAeApp construction

CAeApp::CAeApp() : _orderType(boost::make_shared<COrderTypeModel>()), _presenter(boost::make_shared<CAeAppModel>())
{
    log4cplus::initialize();

    m_Doc = NULL;
    m_bAsOpen           = false;
    m_pCurrentTime      = new ppTime(ppTime::display_hhmmss);
    m_pCurrentDate      = new ppDate();
    IsShowCritics = true;
    IsShowBranchInfo = true;
}

CAeApp::~CAeApp()
{
    if (m_pCurrentTime)
       delete m_pCurrentTime;
    if (m_pCurrentDate)
       delete m_pCurrentDate;
}

void CAeApp::InitOtherViews()
{
    m_pViewLeer = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

    //Initialisierung Kontext
    CCreateContext newContext;
    newContext.m_pNewViewClass = NULL;
    newContext.m_pNewDocTemplate = NULL;
    newContext.m_pLastView = NULL;
    newContext.m_pCurrentFrame = NULL;
    newContext.m_pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();

    //Documentmenber initialisieren
    m_Doc = (CAeDoc *)((CFrameWnd*)m_pMainWnd)->GetActiveDocument();

    //Formviews erzeugen
    m_pViewEing = (CView*) new CAeFView;
    m_pViewEing->Create(NULL, "", WS_CHILD, CRect(0, 0, 0, 0), m_pMainWnd, AFX_IDW_PANE_FIRST + 1, &newContext);
    m_pViewEing->OnInitialUpdate();
}

void CAeApp::InitServerClasses()
{
    m_pCallParameter = new ppCallPlanParameter(ErrorPath());
    m_pCallParameter->SetVertriebsZentrumNr(VzNr());
    if (!m_pCallParameter->GetUni())
       AfxMessageBox("Kein Anrufplan-Parameter vorhanden!");
}

void CAeApp::ExitServerClasses()
{
    if (m_pCallParameter)
        delete m_pCallParameter;
    if (m_pAeUser)
        delete m_pAeUser;

    m_ibtfil.CloseCursor();
    m_vbfil.CloseCursor();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAeApp object
CAeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAeApp initialization

BOOL CAeApp::InitInstance()
{
    //if setting Portnr fails further below, at least try to connect (will lead to error hopefully)
    long Portnr = -1;
    CString server;
    CString strLanguage;

//  scgui::CResizeManager::ex().setFit2Screen(true);

    // CG: The following block was added by the Splash Screen component.
    {
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);
        CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
    }
    char error_msg[81];

    if (!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
        return FALSE;
    }
    //AfxEnableControlContainer();

#ifdef _AFXDLL
    //Enable3dControls();           // Call this when using MFC in a shared DLL
#else
    //Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    //Name der ini-Datei definieren
    {
        char appPath[MAX_PATH] = { 0 };
        GetModuleFileName(NULL, appPath, sizeof(appPath));
        PathRemoveFileSpec(appPath);

        CString tmp(appPath);
        tmp.Append("\\");
        tmp.Append("KSC.INI");

        ErrorPath = appPath;

        //free memory allocated by mfc framework - free is from MSDN
        free((void*)m_pszProfileName);
        //m_pszProfileName needs to be allocated on heap
        m_pszProfileName = _tcsdup((LPCSTR)tmp);
    }
    //Language(error-file aus der ini-Datei laden
    //ErrorPath = GetProfileString("Language","LanguagePath");

    char szBuffer[50];
    DWORD len = sizeof(szBuffer);
    HKEY hKey;
    if (RegOpenKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_BRANCH, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            server = szBuffer;
        }
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_PORTNR, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            Portnr = atol(szBuffer);
        }
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_LANGUAGE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len - 1] = '\0';
            strLanguage = szBuffer;
        }
        RegCloseKey(hKey);
    }
    if (Portnr != 0 && !server.IsEmpty() && !strLanguage.IsEmpty())
    {
        ReadLanguage(strLanguage);
    }

    //Benutzerkennung eingeben
    m_pAeUser = new CAeUser();  //muß vorher schon zugewiesen werden, nicht erst
    CDBenKen dlgBenKen;
    dlgBenKen.m_Server = server;
    if (dlgBenKen.DoModal() != IDOK)
        return FALSE; //IDCANCEL
    m_pAeUser->SetUser(dlgBenKen.m_AeUser);
    m_pAeUser->SetRechner(dlgBenKen.m_Server);
    FilialNr = dlgBenKen.m_FilialNr;
    VzNr = dlgBenKen.m_VzNr;

    if (RegOpenKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_HPBRANCH, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS) //Filialnr in der der User sich am Procenter anmeldet
        {   // Werte gefunden
            szBuffer[len] = '\0';
            ProcenterBranchno = static_cast<short>(atoi(szBuffer));
        }
        else
        {
            ProcenterBranchno = VzNr();
        }
        RegCloseKey(hKey);
    }

    CLGTEXT texte;
    if (strLanguage != Language())
        ReadLanguage(Language());
    SetFilialNrActual(FilialNr());
    if (!m_pAeUser->IsAeUser() && !m_pAeUser->IsInfoListe() && !m_pAeUser->IsOnlyInfo())
    {
        AfxMessageBox(IDP_KEINE_AE_KENN);
        return FALSE; //IDCANCEL
    }
    while (m_pAeUser->IsNoPasswd())
    {
        CDBenKennAend dlgBenKennAend;
        dlgBenKennAend.m_CPwdOld = "xxxxxxxx";
        dlgBenKennAend.DoModal();
    }

    CloseServer(error_msg);    //Benutzerkennungsserver schliessen

//hier eigenen Select auf "lgtextae" anlegen -> fetch-Cursor

    if (OpenAsSession(m_pAeUser->GetRechner()) < 0)
    {
        return FALSE; //IDCANCEL
    }

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(CAeDoc),
    RUNTIME_CLASS(CMainFrame),       // main SDI frame window
    RUNTIME_CLASS(CAeView));
    AddDocTemplate(pDocTemplate);
    OnFileNew();
    InitOtherViews();

    InitServerClasses();
    for (;;)
    {
        m_vbfil.SelVbFilialen(1);
        if (m_vbfil.rc == SRV_SQLNOTFOUND)
            break;
    }
    for (;;)
    {
        m_ibtfil.SelIBTBranches(1);
        if (m_ibtfil.rc == SRV_SQLNOTFOUND)
            break;
    }

    CFORBIDDENWORDS forbiddenwords;
    ppString wort;
    forbiddenwords.SetBranchno(VzNr());
    for (;;)
    {
        if (forbiddenwords.SelWords())
            break;
        SetForbiddenWords(forbiddenwords.GetForbiddenword(wort));
    }
    CPARAMETER parameter;    //Faxadresse einlesen
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("AE");
    parameter.SetZweck("Callback");
    parameter.SetParametername("ConcernWording");
    if ((parameter.SelParameter() == SRV_OK) && (parameter.GetWert() == 1))
    {
        IsConcernWording = true;
    }
    parameter.SetFilialnr(VzNr());
    parameter.SetProgrammname("AE");
    parameter.SetZweck("SAP");
    parameter.SetParametername("UseReferenceNo");
    if ((parameter.SelParameter() == SRV_OK) && (parameter.GetWert() == 1))
    {
        UseSapReferenceNo = true;
    }
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("CSVIMPORTKENNUNG");
    if (parameter.SelZweck() == SRV_OK)
    {
        ppString csPWD;
        ppString csName;
        ImportUser = parameter.GetParametername(csName);
        ImportPWD = parameter.GetAuspraegung(csPWD);
    }
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("TRACE");
    parameter.SetParametername("LOGGING");
    if (!parameter.SelParameter())
    {
        m_AeLogging.SetLoggingLevel((short)parameter.GetWert());
    }
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("CSVIMPORTSERVER");
    if (parameter.SelZweck() == SRV_OK)
    {
        ppString csAdresse;
        ppString csServer;
        ImportAdresse = parameter.GetAuspraegung(csAdresse);
        ImportServer = parameter.GetParametername(csServer);
    }
    parameter.ClearStruct();
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("CSVENCODINGLOCALE");
    parameter.SetParametername("Input");
    if (parameter.SelParameter() == SRV_OK)
    {
        ppString value;
        InputEncoding = parameter.GetAuspraegung(value);
    }
    parameter.ClearStruct();
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("CSVENCODINGLOCALE");
    parameter.SetParametername("Output");
    if (parameter.SelParameter() == SRV_OK)
    {
        ppString value;
        OutputEncoding = parameter.GetAuspraegung(value);
    }
    parameter.ClearStruct();
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("FAX");
    if (parameter.SelZweck() == SRV_OK)
    {
        ppString csFax;
        ppString csName;
        FaxAdresse = parameter.GetAuspraegung(csFax);
        if (parameter.GetWert() > 0)  // in Wert ist die Landesvorwahl gestpeichert
        {
            CString fax;
            fax.Format("00%d", parameter.GetWert());
            FaxLand = fax;
        }
        parameter.GetParametername(csName);
        IsNewFax = (csName == "Faxservernameneu");
    }
    if (IsNewFax())
    {
        parameter.SetFilialnr(0);    //momentan filialunabhängig
        parameter.SetProgrammname("KSC");
        parameter.SetZweck("SAMBA");
        ppString csUser;
        ppString csPWD;
        if (parameter.SelZweck() == SRV_OK)
        {
            FaxUser = parameter.GetParametername(csUser);
            FaxPWD = parameter.GetAuspraegung(csPWD);
        }
    }
    parameter.SetFilialnr(VzNr());
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("TRACE");
    IsLogging = false;
    m_ProCenter.TraceOnOff(FALSE);
    if (parameter.SelZweck() == SRV_OK)
    {
        if (parameter.GetWert() > 0)  // in Wert steht ob geloggt wird
        {
            IsLogging = true;
            m_ProCenter.TraceOnOff(TRUE);
        }
    }
    parameter.SetFilialnr(0);    //momentan filialunabhängig
    parameter.SetProgrammname("KSC");
    parameter.SetZweck("CALLBACK");
    StartNoCallback = 0;
    if (parameter.SelZweck() == SRV_OK)
    {
        StartNoCallback = parameter.GetWert(); // in Wert steht ab welcher Nummer die Rückrufpartner beginnen
    }
    CPARAART paraart; //vorhandene Auftragarten einlesen
    paraart.s.BRANCHNO = VzNr();
    for (;;)
    {
        paraart.s.FETCH_REL = 1;              //normaler Fetch
        paraart.Server(AafilSelaart);
        if (paraart.rc == SRV_SQLNOTFOUND)
        {
            paraart.s.FETCH_REL = 0;          //close Cursor
            paraart.Server(AafilSelaart);
            break;
        }
        AllgEntfSpaces(paraart.s.KDAUFTRAGART);
        m_Auftragarten.Add(paraart.s.KDAUFTRAGART);
    } //Ende der for()-Schleife
    CPARAUFBEARB paraaufbearb;
    paraaufbearb.s.FILIALNR = VzNr();
    paraaufbearb.Server(AafilSelaufbearb);
    DurchlaufZeit = paraaufbearb.s.DURCHLAUFNORMAL;
    Verspaetung = paraaufbearb.s.TOURVERSPAETUNG;
    IsCrema = (paraaufbearb.s.SCREMA[0] == '1');
    IsStopCrema = (paraaufbearb.s.SSTOPCREMA == 1);
    IsCollOrders = (paraaufbearb.s.DELAYEDDAYS > 0);
    Wake1 = paraaufbearb.s.WAKETIME1;
    Wake2 = paraaufbearb.s.WAKETIME2;
    IsNewSuivra = (paraaufbearb.s.SIBTCSTORG[0] == '1');
    IsIBTdirect = (paraaufbearb.s.SCLOSEIBTATONCE == 1);
    UseTourManager = paraaufbearb.s.USETOURMANAGER;
    UseTourManagerCst = UseTourManager();
    if (paraaufbearb.s.SWNEWCALLBACK == 1)
    {
        IsNewCallback = true;
        IsNewCallbackHome = true;
    }
    else
    {
        IsNewCallback = false;
        IsNewCallbackHome = false;
    }
    if (paraaufbearb.s.SDISPOIMPORT == 1)
    {
        IsDispoImport = true;
        IsDispoImportCst = true;
    }
    else
    {
        IsDispoImport = false;
        IsDispoImportCst = false;
    }
    IsNLevelIBT = (paraaufbearb.s.NLEVELIBT == 1);
    IsNLevelIBTCst = IsNLevelIBT(); //Für Artikelauskunft vor dem ersten Auftrag
    IsNlSofort = (paraaufbearb.s.SCLOSERESTDELIVERYATONCE == 1);
    IsDispoSofort = (paraaufbearb.s.SCLOSEDISPOATONCE == 1);
    IsNewF6 = (paraaufbearb.s.SNEWF6 == 1);

    // Sprache setzen
    texte.SetLgid(Language());
    texte.SetLanguage();
    // Initialize OLE libraries
    if (!AfxOleInit())
    {
        AfxMessageBox("Ole Failed");
        return FALSE;
    }

    if (!ProCenterName().IsEmpty() && m_pAeUser->IsHiPathUser())
    {
        OnHipathLogon();
    }

    if (IsBG())
    {
        QuotaInheritance = '1';
    }

    _presenter.LeseBranchNames();

    m_AeLogging.WriteLine(1, "ae.cpp", "InitInstance", "Order Entry started");

    return TRUE;
}

int CAeApp::ExitInstance()
{
    char error_msg[81];

    ExitServerClasses();
    CloseAsSession(); //Nordat-ServerSession schliessen
    CloseServer(error_msg);
    m_AeLogging.WriteLine(1, "ae.cpp", "ExitInstance", "Order Entry stopped");


    return CWinAppMultiLang::ExitInstance();
}

BOOL CAeApp::VersionsPruefung()
{
    // TODO: Vergleiche erste 2 (oder 3?) Stellen von AE CSC_CORE_APPLICATION_VERSION vs zaapunix
    return TRUE;
}

int CAeApp::OpenAsSession(CString strRechner)
{
    char error_msg[81] = {0};
    CString AsServer = strRechner;

    AsServer += "\\pipe\\as";

    if (OpenAEConnection(strRechner, PortNr(), error_msg) != 0)
    {
       AfxMessageBox(IDP_KEIN_AA_VERB);
       return -2;
    }
    Rechner = strRechner;
    if (!VersionsPruefung())
        return -2;
    //Oeffnen Nordat-Server
    CAUFTRAG auftrag;
    BeginWaitCursor();
    CString UserName = m_pAeUser->GetUserName();
    CString TermID = m_pAeUser->GetTermID();
    auftrag.s.UID = m_pAeUser->GetUID();
    auftrag.s.VERTRIEBSZENTRUMNR = VzNr();
    AllgStrCopy(auftrag.s.BEMERKUNGEN, AsServer, L_AUFTRAG_BEMERKUNGEN);
    AllgStrCopy(auftrag.s.GERAETNAME, TermID, L_AUFTRAG_GERAETNAME);
    AllgStrCopy(auftrag.s.USERNAME, UserName, L_AUFTRAG_USERNAME);
    auftrag.Server(AasrvOpensession, PIPE_AE_SRV);
    _country.SetCountry(auftrag.s.SUB_ORDER_TYPE);
    if (_country.IsBG())
    {
        encoding::setConvertMode(encoding::CONVERT_CYRILLIC);
    }
    EndWaitCursor();
    if (auftrag.rc < SRV_OK)
        return auftrag.rc;
    else
    {
        m_bAsOpen = true;
    }

    //Initialisierung der Filialdaten
    CFILINF filinf;
    filinf.s.FILIALNR = FilialNr();
    BeginWaitCursor();
    filinf.Server( AafilGet_filiale );
    CREGIONS regions;
    regions.SetRegionno(filinf.s.REGIONNO);
    CPARAUFBEARB paraufbearb;
    paraufbearb.s.FILIALNR = VzNr();
    paraufbearb.Server(AafilSelaufbearb);
    regions.SelRegion();
    ppString region;
    Region = regions.GetRegionname(region);
    EndWaitCursor();
    AllgEntfSpaces(filinf.s.NAME);
    FilialName = filinf.s.NAME;
    AllgEntfSpaces(filinf.s.PROCENTERNAME);
    ProCenterName = filinf.s.PROCENTERNAME;
    AllgEntfSpaces(filinf.s.BALANCE1);
    Balance1 = filinf.s.BALANCE1;
    AllgEntfSpaces(filinf.s.BALANCE2);
    Balance2 = filinf.s.BALANCE2;
    AllgEntfSpaces(filinf.s.PROCENTERLOCATION);
    ProCenterLocation = filinf.s.PROCENTERLOCATION;
    AllgEntfSpaces(filinf.s.VORWAHL);
    Vorwahl = filinf.s.VORWAHL;
    LagerortLen = filinf.s.LAGERORTLEN;
    BGANR_EK = filinf.s.BGANR_EK;
    AllgEntfSpaces(filinf.s.ORT);
    VzOrt = filinf.s.ORT;
    AllgEntfSpaces(filinf.s.TELNR);
    VzTelnr = filinf.s.TELNR;
    AllgEntfSpaces(filinf.s.FAXNR);
    VzFaxnr = filinf.s.FAXNR;
    AllgEntfSpaces(filinf.s.POSTLEITZAHL);
    VzPLZ = filinf.s.POSTLEITZAHL;
    AllgEntfSpaces(filinf.s.STRASSE);
    VzStrasse = filinf.s.STRASSE;
    IsAutoBuchungNachlieferung = (paraufbearb.s.AUTOMNACHLIEF[0] == '1');
    IsCool20 = (paraufbearb.s.SCOOL20 == 1);
    IsBTMextra = (paraufbearb.s.BTM_EXTRA[0] == '1');
    TimeNoBTM = paraufbearb.s.TIME_NO_BTM;
    MaxPosEil = paraufbearb.s.MAXPOSEIL;
    PosZu = paraufbearb.s.ANZPOSZU;
    PriceRange = paraufbearb.s.RANGEPRICEPCT;
    IsIBTdirect = (paraufbearb.s.SCLOSEIBTATONCE == 1);
    IsDayNight = (paraufbearb.s.SDAYNIGHT[0] == '1');
    IsNewDiscount = (paraufbearb.s.SNEWDISCOUNT[0] == '1');
    IsNoValuta = (paraufbearb.s.SNOCHANGEVAL[0] == '1');
    IsKumPos = (paraufbearb.s.SKUMPOS[0] == '1');
    IsPrintCode = (paraufbearb.s.SANZPRINTCODE[0] == '1');
    IsKLClose = (paraufbearb.s.SKLCLOSE[0] == '1');
    m_KombiAKBArt.InitData(VzNr());

    BeginWaitCursor();
    m_bIsCBStatusUsed = CCallbackStatusManager::GetIsCBStatusUsed();
    EndWaitCursor();

    return 0;
}

void CAeApp::CloseAsSession()
{
    char error_msg[81];
    CAUFTRAG auftrag;
    BeginWaitCursor();
    if (m_bAsOpen)
        auftrag.Server(AasrvClosesession, PIPE_AE_SRV);
    CloseServer(error_msg);
    EndWaitCursor();
    m_bAsOpen = false;
}

void CAeApp::DoWaitCursor(int nCode)
{
   if (nCode != 0)
     ::ShowCursor(nCode>0);
   CWinAppMultiLang::DoWaitCursor(nCode);
}

const ppTime& CAeApp::GetCurrentTime()
{
    CTM time;
    time.Server(AafilGetdatetime);
    m_pCurrentTime->SetTime(time.s.ZEIT);
    return *m_pCurrentTime;
}

const ppDate& CAeApp::GetCurrentDate()
{
    CTM date;
    date.Server(AafilGetdatetime);
    m_pCurrentDate->SetDate(date.s.DATUM);
    return *m_pCurrentDate;
}

// App command to run the dialog
void CAeApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAeApp commands

BOOL CAeApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
    if (code == MSGF_DIALOGBOX && lpMsg->message == WM_KEYDOWN)
    {
        //WM_HOOKFKT ist als Message in aa.h definiert
        if (((CAeFView*)m_pViewEing))
        {
            //AeFView ist aktuell, d.h. Auftrag ist offen
            ((CAeFView*)m_pViewEing)->ResetTimeCount();
            if (   ((LPMSG)lpMsg)->wParam == VK_PAUSE           //Beim Druecken der Pause-Taste
                && GetActiveWindow() == m_pMainWnd->m_hWnd )    //und Main window aktiv
            {
                ((CAeFView*)m_pViewEing)->ResetContent();  //Eingabe loeschen
            }
        }
        LRESULT rc = ::SendMessage(GetActiveWindow(), WM_HOOKFKT, 0, (LPARAM)lpMsg);

        if (rc == 1L)
            return 1L; //Message wird nicht weitergeleitet
    }
    else if (code == MSGF_DIALOGBOX && lpMsg->message == WM_SYSKEYDOWN)
    {
        if ((GetKeyState(VK_MENU) & 0x80) == 0x80)
        {
            if (::SendMessage(GetActiveWindow(), WM_HOOKFKT, 0, (LPARAM)lpMsg) == 1L)
                return 1L; //Message wird weitergeleitet
        }
    }

    return CWinAppMultiLang::ProcessMessageFilter(code, lpMsg);
}

void CAeApp::SetView(int nView)
{
    CView* p_ActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();
    CView* p_NewView;

    ASSERT(nView==VIEW_LEER || nView==VIEW_EING || nView==VIEW_BEARB);

    if (nView==VIEW_BEARB)
        p_NewView = m_pViewBearb;
    if (nView==VIEW_EING)
        p_NewView = m_pViewEing;
    else
        p_NewView = m_pViewLeer;

    if (p_ActiveView == p_NewView)
        return;

    UINT temp = ::GetWindowLong(p_ActiveView->m_hWnd, GWL_ID);
    ::SetWindowLong(p_ActiveView->m_hWnd, GWL_ID,
    ::GetWindowLong(p_NewView->m_hWnd, GWL_ID));
    ::SetWindowLong(p_NewView->m_hWnd, GWL_ID, temp);

    CRect rect; // aktuelle View-Größe ermitteln
    p_ActiveView->GetWindowRect(rect);
    m_pMainWnd->ScreenToClient(rect);

    p_ActiveView->ShowWindow(SW_HIDE);
    p_NewView->ShowWindow(SW_SHOW);
    ((CFrameWnd*)m_pMainWnd)->SetActiveView(p_NewView);

    // neuen View in Größe an alten anpassen
    p_NewView->MoveWindow(rect);

    p_NewView->Invalidate();
    m_pMainWnd->Invalidate();
    m_pMainWnd->UpdateWindow();
}

void CAeApp::OnKundeKndWahl()
{
    CString woher;
    woher = "CAeApp::OnKundeKndWahl";
    CDKndWahl dlgKndWahl;
    CDOffAuftr dlgOffAuftr;
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    dlgOffAuftr.m_RegionNr = VzNr();
    dlgOffAuftr.m_VzNr = VzNr();
    dlgOffAuftr.m_bDafue = FALSE;

    if (!(CAeDoc*)((CAeFView*)m_pViewEing)->GetDocument()->IsModified())
    {
        m_ProCenter.SetUserAtWork(woher, TRUE);
    }

    if (m_ProCenter.GetHiPathKndNr() == 0)
    {
        if (dlgOffAuftr.DoModIfZROrdGer() == IDOK)
        {
            ((CAeFView*)m_pViewEing)->OpenOrder(dlgOffAuftr.GetAufNr());
            return; //offener Auftrag wurde gewaehlt
        }
        if (dlgKndWahl.DoModal() == IDOK)
        {
            dlgOffAuftr.m_RegionNr = VzNr();
            if (dlgOffAuftr.DoModIfZROrdKnd(dlgKndWahl.GetKndNr(), dlgKndWahl.GetKndVz()) == IDOK)
            {
                ((CAeFView*)m_pViewEing)->OpenOrder(dlgOffAuftr.GetAufNr());
                return; //offener Auftrag wurde gewaehlt
            }
            SetFilialNrActual(dlgKndWahl.GetKndFiliale());
            VzNr_Kunde = dlgKndWahl.GetKndVz();
            if (IsDayNight() && !dlgKndWahl.IsAktiv())
            {
                if (MsgBoxYesNo(IDP_OPEN_KND_AUFT) == IDNO)
                    return;
            }
            ((CAeFView*)m_pViewEing)->SetOrgFilNr(dlgKndWahl.GetKndOrgFiliale());
            ((CAeFView*)m_pViewEing)->NewOrder(dlgKndWahl.GetKndNr(), dlgKndWahl.GetKndVz());
            return;
        }
    }
    else
    {
        if (dlgOffAuftr.DoModIfZROrdKnd(m_ProCenter.GetHiPathKndNr(), m_ProCenter.GetHiPathVzNr()) == IDOK)
        {
            ((CAeFView*)m_pViewEing)->OpenOrder(dlgOffAuftr.GetAufNr());
            return; //offener Auftrag wurde gewaehlt
        }
        ((CAeFView*)m_pViewEing)->NewOrder(m_ProCenter.GetHiPathKndNr(), m_ProCenter.GetHiPathVzNr());
        return;
    }

    if (!(CAeDoc*)((CAeFView*)m_pViewEing)->GetDocument()->IsModified())
    {
        m_ProCenter.SetUserAtWork(woher, FALSE);
    }
}

void CAeApp::OnUpdateKundeKndWahl(CCmdUI* pCmdUI)
{
    if (   (!m_pAeUser->IsAeUser() && !m_pAeUser->IsOnlyInfo())
        || m_pAeUser->KeinPlan() )
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInfKunde()
{
    //Ausgabe der Kundeninformationen
    CKndInf dlgKndInf;
    if (m_ProCenter.GetHiPathKndNr() != 0)
    {
        CDKndWahl dlgKndWahl;
        dlgKndWahl.m_CKndNr.Format("%d", m_ProCenter.GetHiPathKndNr());
        dlgKndWahl.SetKndVz(m_ProCenter.GetHiPathVzNr());
        dlgKndWahl.SetEnableAeGesperrt();    // Checkbutton muß enabled werden
        if (dlgKndWahl.DoModal() == IDOK)
        {
            dlgKndInf.SetIdfNr(dlgKndWahl.GetKndNr());
            dlgKndInf.SetKndNr(dlgKndWahl.GetKndNr());
            dlgKndInf.SetKndVz(dlgKndWahl.GetKndVz());
        }
    }
    dlgKndInf.DoModal();
}

void CAeApp::OnUpdateInfKunde(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser() && !m_pAeUser->IsOnlyInfo())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInfArt()
{
    CDArtInf dlgArtInf;
    dlgArtInf.DoModal();
}

void CAeApp::OnUpdateInfArt(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser() && !m_pAeUser->IsOnlyInfo())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInfAuf()
{
    if (IsNewF6())
    {
        CDAufAuswahl dlgAufAuswahl;
        if (m_ProCenter.GetHiPathKndNr() != 0)
        {
            dlgAufAuswahl.m_KndNr.Format("%d", m_ProCenter.GetHiPathKndNr());
            dlgAufAuswahl.m_lKndNr          = m_ProCenter.GetHiPathKndNr();
            dlgAufAuswahl.m_IdfNr           = m_ProCenter.GetHiPathKndNr();
            dlgAufAuswahl.m_VzNr            = m_ProCenter.GetHiPathVzNr();
        }
        if (dlgAufAuswahl.DoModal() == IDOK)
        {
            ((CAeFView *)m_pViewEing)->OpenOrder(dlgAufAuswahl.GetAufNr());
            return;
        }
    }
    else
    {
        CDAufInf dlgAufInf;
        if (m_ProCenter.GetHiPathKndNr() != 0)
        {
            dlgAufInf.m_KndNr.Format("%d", m_ProCenter.GetHiPathKndNr());
            dlgAufInf.m_lKndNr          = m_ProCenter.GetHiPathKndNr();
            dlgAufInf.m_IdfNr           = m_ProCenter.GetHiPathKndNr();
            dlgAufInf.m_VzNr            = m_ProCenter.GetHiPathVzNr();
        }
        if (dlgAufInf.DoModal() == IDOK)
        {
            ((CAeFView *)m_pViewEing)->OpenOrder(dlgAufInf.GetAufNr());
            return;
        }
    }
}

void CAeApp::OnUpdateInfAuf(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser() && !m_pAeUser->IsOnlyInfo())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnKundeKundeAusPlan()
{
    GetNextPhoneCall getNextPhoneCall;
    if (IsNoParaCall())
        getNextPhoneCall.NoParaCalls();
    // nase VZ muss noch richtig versorgt werden
    if (getNextPhoneCall.GetCall() != NO_CUSTOMER)
    {
        ((CAeFView*)m_pViewEing)->SetOrgFilNr(getNextPhoneCall.GetKndVZ());
        ((CAeFView*)m_pViewEing)->NewOrder(getNextPhoneCall.GetKndNum(),getNextPhoneCall.GetKndVZ());
        return;
    }
    else
        AfxMessageBox(IDP_NO_RUFE);
}

void CAeApp::OnUpdateKundeKundeAusPlan(CCmdUI* pCmdUI)
{
    if (   !m_pAeUser->IsAeUser()
        || !m_pAeUser->Planteil()
        || m_pAeUser->KeinPlan() )
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnKundeOffeneAuftrge()
{
    CDCheckOpenCallOrOrder dlgCheckOpenCallOrOrder;
    if (dlgCheckOpenCallOrOrder.DoModal() == IDOK)
    {
        if (dlgCheckOpenCallOrOrder.GetOrderNr())
        {
            ((CAeFView*)m_pViewEing)->OpenOrder(dlgCheckOpenCallOrOrder.GetOrderNr());
        }
        else if (dlgCheckOpenCallOrOrder.GetCustomerNr())
        {
            ((CAeFView*)m_pViewEing)->SetOrgFilNr(dlgCheckOpenCallOrOrder.GetVZNr());
            ((CAeFView*)m_pViewEing)->NewOrder( dlgCheckOpenCallOrOrder.GetCustomerNr(), dlgCheckOpenCallOrOrder.GetVZNr() );
        }
    }
}

void CAeApp::OnDeleteReservation()
{
    CDeleteReservation b;
    b.DoModal();
}

void CAeApp::OnUpdateKundeOffeneAuftrge(CCmdUI* pCmdUI)
{
    if (   !m_pAeUser->IsAeUser()
        || m_pAeUser->KeinPlan()
        || !m_pAeUser->Planteil() )
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAuftragDafzurckgestellteauftrge()
{
    CDOffAuftr dlgOffAuftr;
    dlgOffAuftr.m_RegionNr = VzNr();
    dlgOffAuftr.m_VzNr = VzNr();
    dlgOffAuftr.m_Geraet = Geraet();
    if (dlgOffAuftr.DoModal() == IDOK)
    {
        ((CAeFView*)m_pViewEing)->OpenOrder(dlgOffAuftr.GetAufNr());
        return;
    }
}

void CAeApp::OnUpdateAuftragDafzurckgestellteauftrge(CCmdUI* pCmdUI)
{
    if (   !m_pAeUser->IsAeUser()
        || !m_pAeUser->Planteil()
        || m_pAeUser->KeinPlan() )
        pCmdUI->Enable(FALSE);
}

BOOL CAeApp::PreTranslateMessage(MSG* pMsg)
{
    // CG: The following line was added by the Splash Screen component.
    CSplashWnd::PreTranslateAppMessage(pMsg);

    return CWinAppMultiLang::PreTranslateMessage(pMsg);
}

void CAeApp::OnKombAuftBuchArt()
{
    CDParKaBaKomb dlgParKaBaKomb;
    dlgParKaBaKomb.DoModal();
}

void CAeApp::OnUpdateKombAuftBuchArt(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParKaBaKomb())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnDefBuchart()
{
    CDParBuchArt dlgParBuchArt;
    dlgParBuchArt.DoModal();
}

void CAeApp::OnUpdateDefBuchart(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParBuchArt())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnDefKommiarten()
{
    CDParKomArt dlgParKomArt;
    dlgParKomArt.DoModal();
}

void CAeApp::OnUpdateDefKommiarten(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParKommArt())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnDefKondgrp()
{
    CDParKondGrp dlgParKondGrp;
    dlgParKondGrp.DoModal();
}

void CAeApp::OnUpdateDefKondgrp(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParKondGr())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnDefAuftrart()
{
    CDParAufArt dlgParAufArt;
    dlgParAufArt.DoModal();
}

void CAeApp::OnUpdateDefAuftrart(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParAuftrArt())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnParAufbearb()
{
    CDParAufBearb dlgParAufBearb;
    dlgParAufBearb.m_FilialNr = VzNr();
    dlgParAufBearb.DoModal();
}

void CAeApp::OnUpdateParAufbearb(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParAufBearb() && !m_pAeUser->IsEnableWerbeFach())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnParAufbearberg()
{
    CDChooseFiliale dlgChooseFiliale;
    CDParAufBearbErg dlgParAufBearbErg;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    dlgParAufBearbErg.m_FilialNr = dlgChooseFiliale.m_FilialNr;
    dlgParAufBearbErg.DoModal();
}

void CAeApp::OnUpdateParAufbearberg(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParAufBeErg())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnParKobehtyp()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CDParKoBehTyp dlgParKoBehTyp;
    dlgParKoBehTyp.m_FilialNr = dlgChooseFiliale.m_FilialNr;
    dlgParKoBehTyp.DoModal();
}

void CAeApp::OnUpdateParKobehtyp(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParKomBehTyp())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnParKommi()
{
    AfxMessageBox("Noch nicht implementiert");
}

void CAeApp::OnUpdateParKommi(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParKommi())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnParNachrart()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CDParNachart dlgParNachart;
    dlgParNachart.m_FilialNr = dlgChooseFiliale.m_FilialNr;
    dlgParNachart.DoModal();
}

void CAeApp::OnUpdateParNachrart(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParNachrArten())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHilsprogKennwort()
{
    CDBenKennAend dlgBenKennAend;
    dlgBenKennAend.DoModal();
}

void CAeApp::OnUpdateHilsprogKennwort(CCmdUI* /*pCmdUI*/)
{
}

void CAeApp::OnHilfsprTaschenrechner()
{
   HWND hCalcWnd = ::FindWindow("SciCalc",NULL);
   if (hCalcWnd!=NULL)
   {
      ::BringWindowToTop(hCalcWnd);          //in Vordergrund holen
      ::ShowWindow(hCalcWnd,SW_SHOWNORMAL);  //restourieren, falls minimized
   }
   else if (WinExec("CALC.EXE",SW_SHOW) < 32)
   {
      AfxMessageBox(IDP_ERR_AUFR_CALC);
   }
}

void CAeApp::OnUpdateHilfsprTaschenrechner(CCmdUI* /*pCmdUI*/)
{
}

void CAeApp::OnHilfsprogrammeBenverw()
{
    CDBenVwtng dlgBenVwtng;
    dlgBenVwtng.DoModal();
}

void CAeApp::OnUpdateHilfsprogrammeBenverw(CCmdUI* pCmdUI)
{
    if (   !m_pAeUser->UpdUser()
        || (m_pAeUser->GetRechner() != Rechner() && !m_pAeUser->IsAdminAndereFiliale()) )
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeApp::OnFastOpenOrder()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_FAST_OPEN_ORDER, MF_BYCOMMAND) == MF_CHECKED)
        IsFastOpenOrder = false; //check war vorher !!!
    else
        IsFastOpenOrder = true;
}

void CAeApp::OnUpdateFastOpenOrder(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsFastOpenOrder() ? 1 : 0);
    }
}

void CAeApp::OnExtrasAnrufplanzuerstabarbeiten()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_ANRUFPLANZUERSTABARBEITEN, MF_BYCOMMAND) == MF_CHECKED)
        IsAnrufPlan = false;  //check war vorher !!!
    else
        IsAnrufPlan = true;
}

void CAeApp::OnUpdateExtrasAnrufplanzuerstabarbeiten(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsAnrufPlan() ? 1 : 0);
    }
}


void CAeApp::OnExtrasKeineparaanrufe()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_KEINEPARAANRUFE, MF_BYCOMMAND) == MF_CHECKED)
        IsNoParaCall = false; //check war vorher !!!
    else
        IsNoParaCall = true;
}

void CAeApp::OnUpdateExtrasKeineparaanrufe(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsNoParaCall() ? 1 : 0);
    }
}

void CAeApp::OnSortzurorderAuftragsnr()
{
    OrderSort = SORT_ORDER_ORDNUMBER;
}

void CAeApp::OnUpdateSortzurorderAuftragsnr(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_ORDNUMBER)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnSortzurorderAposchlz()
{
    OrderSort = SORT_ORDER_APO_ENDE;
}

void CAeApp::OnUpdateSortzurorderAposchlz(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_APO_ENDE)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnSortzurorderIdf()
{
    OrderSort = SORT_ORDER_IDF;
}

void CAeApp::OnUpdateSortzurorderIdf(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_IDF)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnSortzurorderTour()
{
    OrderSort = SORT_ORDER_TOUR;
}

void CAeApp::OnUpdateSortzurorderTour(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_TOUR)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}


void CAeApp::OnInformationenInfoliste()
{
    CDInfoListe dlgInfoListe;
    dlgInfoListe.DoModal();
}

void CAeApp::OnUpdateInformationenInfoliste(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser() && !m_pAeUser->IsInfoListe())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInformationenStatusauftragsverarbeitung()
{
    CDAeStatusAe dlgAeStatusAe;
    dlgAeStatusAe.DoModal();
}

void CAeApp::OnUpdateInformationenStatusauftragsverarbeitung(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->StatusErl())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAuftragStatistik()
{
    CDAutrStat dlgAutrStat;
    dlgAutrStat.DoModal();
}

void CAeApp::OnUpdateAuftragStatistik(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->AnzFilialUms())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInformationenTouren()
{
    CDTourAusw dlgTourAusw;
    dlgTourAusw.DoModal();
}

void CAeApp::OnUpdateInformationenTouren(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInformationenTagesanrufplan()
{
    CDPlanTag dlgPlanTag;
    dlgPlanTag.DoModal();
}

void CAeApp::OnUpdateInformationenTagesanrufplan(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInfoUpd()
{
    CDInfoUpd dlgInfoUpd;
    dlgInfoUpd.DoModal();
}

void CAeApp::OnUpdateInfoUpd(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdInfo())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAltfilUpd()
{
    if (UseTourManager() > 0)
    {
        CDIbtBranches dlgIbtBranches;
        if (IsNLevelIBT())
        {
            dlgIbtBranches.m_bNLevelIBT = TRUE;
        }
        dlgIbtBranches.DoModal();
    }
    else
    {
        CAltFil dlgAltFil;
        dlgAltFil.m_FilialNr = VzNr();
        dlgAltFil.DoModal();
    }
}

void CAeApp::OnUpdateAltfilUpd(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdAltfil())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnZeitartUpd()
{
    CDZeitart dlgZeitart;
    dlgZeitart.DoModal();
}

void CAeApp::OnUpdateZeitartUpd(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdZeitart())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInformationenSeralog()
{
    CDSeralog dlgSeralog;
    dlgSeralog.DoModal();
}

void CAeApp::OnUpdateInformationenSeralog(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAeAuftrEntsp()
{
    CEntsperr dlgEntsperr;
    dlgEntsperr.DoModal();
}

void CAeApp::OnUpdateAeAuftrEntsp(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdEntsperr())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnBearbeitenNachlieferpositionen()
{
    CDUpdNachl dlgUpdNachl;
    dlgUpdNachl.DoModal();
}

void CAeApp::OnUpdateBearbeitenNachlieferpositionen(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAuftragFfnenparaauftrag()
{
    ((CAeFView *)m_pViewEing)->OpenParaOrder();
}

void CAeApp::OnUpdateAuftragFfnenparaauftrag(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser() || !m_pAeUser->Planteil())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnVerwaltungAnzeigebenutzerliste()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CDAnzAeUser dlgAnzAeUser;
    dlgAnzAeUser.m_FilialNr = dlgChooseFiliale.m_FilialNr;
    dlgAnzAeUser.DoModal();
}

void CAeApp::OnUpdateVerwaltungAnzeigebenutzerliste(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnVerwaltungRufzeitenabweichungendefinieren()
{
    CDPlanAbweichung dlgPlanAbweichung;
    dlgPlanAbweichung.DoModal();
}

void CAeApp::OnUpdateVerwaltungRufzeitenabweichungendefinieren(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdRufpAbw())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnBearbeitenLagerendkontrolle()
{
    CWeLaEkLs dlgWeLaEkLs;
    dlgWeLaEkLs.DoModal();
}

void CAeApp::OnUpdateBearbeitenLagerendkontrolle(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnBearbeitenNachlieferpositionenKnd()
{
    CAeKndNachl dlgAeKndNachl;
    dlgAeKndNachl.DoModal();
}

void CAeApp::OnUpdateBearbeitenNachlieferpositionenKnd(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnProtNachlifbearb()
{
    CDProtNachLief dlgProtNachLief;
    dlgProtNachLief.DoModal();
}

void CAeApp::OnUpdateProtNachlifbearb(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnParAuftrendzeit()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CDParAuftrendzeit dlgParAuftrendzeit;
    dlgParAuftrendzeit.m_FilialNr = dlgChooseFiliale.m_FilialNr;
    dlgParAuftrendzeit.DoModal();
}

void CAeApp::OnUpdateParAuftrendzeit(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParAuftrArt())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnKndAuftragart()
{
    CDAuftragartKd dlgAuftragartKd;
    dlgAuftragartKd.DoModal();
}

void CAeApp::OnUpdateKndAuftragart(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdKndAufArt())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasKundeIdf()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_KUNDE_IDF, MF_BYCOMMAND) == MF_CHECKED)
        IsKundeIDF = false; //check war vorher !!!
    else
        IsKundeIDF = true;
}

void CAeApp::OnUpdateExtrasKundeIdf(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsKundeIDF() ? 1 : 0);
    }
}

void CAeApp::OnExtrasPznDirekt()
{
    BeginWaitCursor();
    CString name = m_pAeUser->GetUserName();
    m_pAeUser->InitUser(name);
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_PZN_DIREKT, MF_BYCOMMAND) == MF_CHECKED)
        m_pAeUser->SetDirektPZN(FALSE);    //check war vorher !!!
    else
        m_pAeUser->SetDirektPZN(TRUE);
    m_pAeUser->UpdateUserDB();
    EndWaitCursor();
}

void CAeApp::OnUpdateExtrasPznDirekt(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(m_pAeUser->DirektPZN() ? 1 : 0);
    }
}

void CAeApp::OnVerwaltungCallback()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CPARAUFBEARB paraaufbearb;
    paraaufbearb.s.FILIALNR = dlgChooseFiliale.m_FilialNr;
    paraaufbearb.Server( AafilSelaufbearb );
    AeGetApp()->IsNewCallback = (paraaufbearb.s.SWNEWCALLBACK == 1);
    if (IsNewCallback())
    {
        CDUpdDivision dlgUpdDivision;
        dlgUpdDivision.SetVzNr(dlgChooseFiliale.m_FilialNr);
        dlgUpdDivision.DoModal();
    }
    else
    {
        CDUpdPartner dlgUpdPartner;
        dlgUpdPartner.SetVzNr(dlgChooseFiliale.m_FilialNr);
        dlgUpdPartner.DoModal();
    }
    IsNewCallback = IsNewCallbackHome();
}

void CAeApp::OnUpdateVerwaltungCallback(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdCallback())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasAttachPartner()
{
    CDAttachPartner dlgAttachPartner;
    dlgAttachPartner.DoModal();
}

void CAeApp::OnUpdateExtrasAttachPartner(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnVerwaltungFilialpartner()
{
    CDFilialpartner dlgFilialpartner;
    dlgFilialpartner.DoModal();
}

void CAeApp::OnUpdateVerwaltungFilialpartner(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdParAufBearb())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasRrMeld()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_RR_MELD, MF_BYCOMMAND) == MF_CHECKED)
        IsRRMeld = false; //check war vorher !!!
    else
        IsRRMeld = true;
}

void CAeApp::OnUpdateExtrasRrMeld(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsRRMeld() ? 1 : 0);
    }
}

void CAeApp::OnAeRrEntsp()
{
    CDRrUnlock dlgRrUnlock;
    dlgRrUnlock.DoModal();
}

void CAeApp::OnUpdateAeRrEntsp(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdEntsperr())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasRrNotDone()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_RR_NOT_DONE, MF_BYCOMMAND) == MF_CHECKED)
        IsRRNotDone = false;  //check war vorher !!!
    else
        IsRRNotDone = true;
}

void CAeApp::OnUpdateExtrasRrNotDone(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsRRNotDone() ? 1 : 0);
    }
}

void CAeApp::OnExtrasNoBeep()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NO_BEEP, MF_BYCOMMAND) == MF_CHECKED)
        IsNoBeep = false; //check war vorher !!!
    else
        IsNoBeep = true;
}

void CAeApp::OnUpdateExtrasNoBeep(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsNoBeep() ? 1 : 0);
    }
}

void CAeApp::OnAnrufplanMasterplanPflege()
{
    CString woher;
    woher = "CAeApp::OnAnrufplanMasterplanPflege";
    ppCustomerDisplay Customer(ErrorPath());
    CCPCallPlanMaintenance dlgCallPlanMaintenance(&Customer);
    if (!(CAeDoc*)((CAeFView*)m_pViewEing)->GetDocument()->IsModified())
    {
        m_ProCenter.SetUserAtWork(woher, TRUE);
    }

    dlgCallPlanMaintenance.DoModal();

    if (!(CAeDoc*)((CAeFView*)m_pViewEing)->GetDocument()->IsModified())
    {
        m_ProCenter.SetUserAtWork(woher, FALSE);
    }
}

void CAeApp::OnUpdateAnrufplanMasterplanPflege(CCmdUI* /*pCmdUI*/)
{
}

void CAeApp::OnRufadminAbweichung()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CCPCallPlanLoadListe dlgCallPlanLoadListe;
    dlgCallPlanLoadListe.SetVzNr(dlgChooseFiliale.m_FilialNr);
    dlgCallPlanLoadListe.DoModal();
}

void CAeApp::OnUpdateRufadminAbweichung(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->Anrufplanuebernahme())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnRufadminUebernahme()
{
    CCPCallPlanUndertake dlgCallPlanUndertake;
    dlgCallPlanUndertake.DoModal();
}

void CAeApp::OnUpdateRufadminUebernahme(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->Anrufplanuebernahme())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAnrufplanverwaltungRegionenfestlegen()
{
    CCPRegionMaintenance dlgRegionMaintenance;
    dlgRegionMaintenance.DoModal();
}

void CAeApp::OnUpdateAnrufplanverwaltungRegionenfestlegen(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->Regionenverwalten())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAnrufplanverwaltungLokaleeinstellungen()
{
    CPLocalOptions dlgPLocalOptions;
    dlgPLocalOptions.DoModal();
}

void CAeApp::OnUpdateAnrufplanverwaltungLokaleeinstellungen(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdSeraPlan())
        pCmdUI->Enable(FALSE);
}

int CAeApp::ChangeBranch(CString Server, short sFilialNr)
{
    if (!m_pAeUser->ChangeFiliale())
        return 1;
    short saveFilialNr = FilialNr();
    FilialNr = sFilialNr;
    (((CFrameWnd*) m_pMainWnd)->GetActiveView())->PostMessage(WM_KILLTIMER, IDOK, NULL);
    CloseAsSession();
    int rc = OpenAsSession(Server);
    if (rc < 0)
    {
        FilialNr = saveFilialNr;
        return rc;
    }
    (((CFrameWnd*)m_pMainWnd)->GetActiveView())->PostMessage(WM_ACTTIMER, IDOK, NULL);
    return 0;
}

const std::vector<Filiale>& CAeApp::HoleFilialen()
{
    return _presenter.GetBranchesOfRegion(VzNr());
}

void CAeApp::SetFilialNrActual(short fili)
{
    CFILINF filinf;
    FilialNrActual = fili;
    filinf.s.FILIALNR = FilialNrActual();
    BeginWaitCursor();
    filinf.Server(AafilSet_actualfiliale);
    EndWaitCursor();
}

void CAeApp::OnAuswertMaster()
{
    CString woher;
    woher = "CAeApp::OnAuswertMaster";
    if (!(CAeDoc*)((CAeFView*)m_pViewEing)->GetDocument()->IsModified())
    {
        m_ProCenter.SetUserAtWork(woher,TRUE);
    }

    CNMDProgress dlgProgress;
    dlgProgress.SetText("Masterplanliste wird erstellt");
    if (dlgProgress.GetSafeHwnd() == 0)
        dlgProgress.Create();
    BeginWaitCursor();
    CDRUCKPARA dr;
    dr.s.VERTRIEBSZENTRUMNR = VzNr();
    dr.s.POSART[0] = '0';
    dr.s.POSART[1] = '0';
    if (dlgProgress.GetSafeHwnd() != 0)
        dlgProgress.SetProgress(5);
    for (;;)
    {
        dr.Server(AadruckMasterplan);
        if (dr.rc != SRV_OK)
            break;
        if (dlgProgress.GetSafeHwnd() != 0)
            dlgProgress.SetProgress(dr.s.VERTRIEBSZENTRUMNR);
    }
    if (dlgProgress.GetSafeHwnd() != 0)
        dlgProgress.DestroyWindow();
    EndWaitCursor();

    if (!(CAeDoc*)((CAeFView*)m_pViewEing)->GetDocument()->IsModified())
    {
        m_ProCenter.SetUserAtWork(woher, FALSE);
    }
}

void CAeApp::OnUpdateAuswertMaster(CCmdUI* /*pCmdUI*/)
{
}

void CAeApp::OnAnrufplanverwaltungKundendatenDafenummerndern()
{
    CCPCustomerTelNo dlgCustomerTelNo;
    dlgCustomerTelNo.DoModal();
}

void CAeApp::OnUpdateAnrufplanverwaltungKundendatenDafenummerndern(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdSeraPlan())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnAnrufplanverwaltungKundendatenKundeneigenschaften()
{
    CCPCustomerProperties dlgCustomerProperties;
    dlgCustomerProperties.DoModal();
}

void CAeApp::OnUpdateAnrufplanverwaltungKundendatenKundeneigenschaften(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdSeraPlan())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInformationenNotdienst()
{
    CDAeNotdienst dlgAeNotdienst;
    dlgAeNotdienst.DoModal();
}

void CAeApp::OnUpdateInformationenNotdienst(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasPosZusammen()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_POS_ZUSAMMEN, MF_BYCOMMAND) == MF_CHECKED)
        IsPosZusammen = false;   //check war vorher !!!
    else
        IsPosZusammen = true;
}

void CAeApp::OnUpdateExtrasPosZusammen(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsPosZusammen() ? 1 : 0);
    }
}

void CAeApp::OnExtrasNichtMeldAuftragOffen()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NICHT_MELD_AUFTRAG_OFFEN, MF_BYCOMMAND) == MF_CHECKED)
        IsOffAufMeld = false;    //check war vorher !!!
    else
        IsOffAufMeld = true;
}

void CAeApp::OnUpdateExtrasNichtMeldAuftragOffen(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsOffAufMeld() ? 1 : 0);
    }
}

void CAeApp::OnInformationenLagerrevision()
{
    CDLagerrevision dlgLagerrevision;
    dlgLagerrevision.DoModal();
}

void CAeApp::OnUpdateInformationenLagerrevision(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->Bewegungen())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInformationenArtikelkonto()
{
    CDArtikelkonto dlgArtikelkonto;
    dlgArtikelkonto.DoModal();
}

void CAeApp::OnUpdateInformationenArtikelkonto(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->Bewegungen() && !m_pAeUser->IsOnlyInfo())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasAuswahlKurz()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_AUSWAHL_KURZ, MF_BYCOMMAND) == MF_CHECKED)
        IsAuswahlKurz = false;   //check war vorher !!!
    else
        IsAuswahlKurz = true;
}

void CAeApp::OnUpdateExtrasAuswahlKurz(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsAuswahlKurz() ? 1 : 0);
    }
}

void CAeApp::OnExtrasAnzeigeAllePos()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_ANZEIGE_ALLE_POS, MF_BYCOMMAND) == MF_CHECKED)
        IsAnzeigeAlle = false;   //check war vorher !!!
    else
        IsAnzeigeAlle = true;
}

void CAeApp::OnUpdateExtrasAnzeigeAllePos(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsAnzeigeAlle() ? 1 : 0);
    }
}

void CAeApp::OnExtrasAnzeigeAlleDef()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_ANZEIGE_ALLE_DEF, MF_BYCOMMAND) == MF_CHECKED)
        IsAnzeigeAlleDef = false;    //check war vorher !!!
    else
        IsAnzeigeAlleDef = true;
}

void CAeApp::OnUpdateExtrasAnzeigeAlleDef(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsAnzeigeAlleDef() ? 1 : 0);
    }
}

void CAeApp::OnSortzurorderAart()
{
    OrderSort = SORT_ORDER_AART;
}

void CAeApp::OnUpdateSortzurorderAart(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_AART)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnExtrasVerarbRegio()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_VERARB_REGIO, MF_BYCOMMAND) == MF_CHECKED)
        IsKundeHome = true;  //check war vorher !!!
    else
        IsKundeHome = false;
}

void CAeApp::OnUpdateExtrasVerarbRegio(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsKundeHome() ? 0 : 1);
    }
}

void CAeApp::OnPflegeSonderTouren()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CDSonderTouren dlgSonderTouren;
    dlgSonderTouren.SetVzNr(dlgChooseFiliale.m_FilialNr);
    dlgSonderTouren.DoModal();
}

void CAeApp::OnUpdatePflegeSonderTouren(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdKndAufArt())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnMailVz()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_MAIL_VZ, MF_BYCOMMAND) == MF_CHECKED)
        IsMailVzEigen = false;   //check war vorher !!!
    else
        IsMailVzEigen = true;
}

void CAeApp::OnUpdateMailVz(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->UpdMailUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsMailVzEigen() ? 1 : 0);
    }
}

void CAeApp::OnExtrasSofort() //Sofort abschliessen in F4 bei MD
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_SOFORT, MF_BYCOMMAND) == MF_CHECKED)
        IsSofort = false;  //check war vorher !!!
    else
        IsSofort = true;
}

void CAeApp::OnUpdateExtrasSofort(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsSofort() ? 1 : 0);
    }
}

void CAeApp::OnHipathLogoff()
{
    TRACE("OnHipathLogoff\n");
    m_AeTrace.WriteTrace("", "", "OnHipathLogoff\n");

    m_ProCenter.AgentLogOff();
    m_ProCenter.SetHiPathLogon(FALSE);
}

void CAeApp::OnUpdateHipathLogoff(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathLogoff\n");
    if (m_ProCenter.IsHiPathConnected() && m_ProCenter.IsHiPathLogon())
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathLogon()
{
    TRACE("OnHipathLogon\n");
    m_AeTrace.WriteTrace("", "", "OnHipathLogon\n");

    CDHPLogon dlgHPLogon;
    dlgHPLogon.DoModal();
}

void CAeApp::OnUpdateHipathLogon(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathLogon\n");
    if (ProCenterName().IsEmpty())
    {
        pCmdUI->Enable(FALSE);
        return;
    }
    if (!m_pAeUser->IsHiPathUser())
        pCmdUI->Enable(FALSE);
    else if (!m_ProCenter.IsHiPathLogon())
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathPauseStart()
{
    TRACE("OnHipathPauseStart\n");
    m_AeTrace.WriteTrace("", "", "OnHipathPauseStart\n");

    CString woher;
    woher = "CAeApp::OnHipathPauseStart";
    m_AeTrace.WriteTrace(woher,"AeApp","AgentUnAvail");
    m_ProCenter.AgentUnAvail(0);
    m_ProCenter.SetHiPathPause(TRUE);
}

void CAeApp::OnUpdateHipathPauseStart(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathPauseStart\n");

    if (m_ProCenter.IsHiPathLogon() && !m_ProCenter.IsHiPathPause())
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathPauseStop()
{
    TRACE("OnHipathPauseStop\n");
    m_AeTrace.WriteTrace("", "", "OnHipathPauseStop\n");

    CString woher;
    woher = "CAeApp::OnHipathPauseStop";
    m_AeTrace.WriteTrace(woher,"AeApp","AgentAvail");
    m_ProCenter.AgentAvail();
    m_ProCenter.SetHiPathPause(FALSE);
}

void CAeApp::OnUpdateHipathPauseStop(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathPauseStop\n");

    if (m_ProCenter.IsHiPathLogon() && m_ProCenter.IsHiPathPause())
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathCall()
{
    TRACE("OnHipathCall\n");
    m_AeTrace.WriteTrace("", "", "OnHipathCall\n");

    CDHPMakeCall dlgHPMakeCall;
    if (dlgHPMakeCall.DoModal() == IDOK)
    {
        CString cTelNr = '0' + dlgHPMakeCall.m_csTelNr;
        m_ProCenter.MakeCall(cTelNr);
    }
}

void CAeApp::OnUpdateHipathCall(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathCall\n");

    if (m_ProCenter.IsHiPathLogon() && !m_ProCenter.IsHiPathOpen() && !m_ProCenter.IsHiPathCallActiv())
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathCallEnd()
{
    TRACE("OnHipathCallEnd\n");
    m_AeTrace.WriteTrace("", "", "OnHipathCallEnd\n");

    m_ProCenter.DisconnectCall();
    m_ProCenter.SetHiPathCallActiv(FALSE);
}

void CAeApp::OnUpdateHipathCallEnd(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathCallEnd\n");

    if (m_ProCenter.IsHiPathLogon() && m_ProCenter.IsHiPathCallActiv())
        pCmdUI->Enable(TRUE);
    else
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnInfoUpdZent()
{
    CDInfoUpdZ dlgInfoUpdZ;
    dlgInfoUpdZ.DoModal();
}

void CAeApp::OnUpdateInfoUpdZent(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsInfoPflege())
        pCmdUI->Enable(FALSE);
}

void CAeApp::ReadLanguage(CString Language)
{
    scgui::CResStringBase::ECodepage cp = (Language == "BG") ? scgui::CResStringBase::CP_CYRILLIC : scgui::CResStringBase::CP_WEST;
    CString FileName;
    FileName.Format("ae_%s.txt", Language.GetString());
    if (Language == "DE")
        CResString::ex().initCustom();
    else
        CResString::ex().initByFile(FileName, cp);
    Letter_A = CResString::ex().getStrTblText(AETXT_FIRST_LETTER).GetAt(0);
    Letter_Z = CResString::ex().getStrTblText(AETXT_LAST_LETTER).GetAt(0);
    Letter_a = CResString::ex().getStrTblText(AETXT_FIRST_LETTER_LOW).GetAt(0);
    Letter_z = CResString::ex().getStrTblText(AETXT_LAST_LETTER_LOW).GetAt(0);
}

void CAeApp::OnExtrasMatchcode()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_MATCHCODE, MF_BYCOMMAND) == MF_CHECKED)
        IsMatchCode = false;    //check war vorher !!!
    else
        IsMatchCode = true;
}

void CAeApp::OnUpdateExtrasMatchcode(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsMatchCode() ? 1 : 0);
    }
}

void CAeApp::OnPflegeKundenrufweiterleitungpflegen()
{
    CDCustomerRouting dlgCustomerRouting;
    dlgCustomerRouting.DoModal();
}

void CAeApp::OnUpdatePflegeKundenrufweiterleitungpflegen(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsPflegeRufweiter())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathTrace()
{
    TRACE("OnHipathTrace\n");
    m_AeTrace.WriteTrace("", "", "OnHipathTrace\n");

    if (m_pMainWnd->GetMenu()->GetMenuState(ID_HIPATH_TRACE, MF_BYCOMMAND) == MF_CHECKED)
    {
        m_bTrace = false;    //check war vorher !!!
        IsLogging = false;
        m_ProCenter.TraceOnOff(FALSE);
    }
    else
    {
        IsLogging = true;
        m_bTrace = true;
        m_ProCenter.TraceOnOff(TRUE);
    }
}

void CAeApp::OnUpdateHipathTrace(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathTrace\n");

    if (!m_pAeUser->IsHiPathUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(m_bTrace ? 1 : 0);
    }
}

void CAeApp::OnInformationenStockentry()
{
    CDStockEntry dlgStockEntry;
    dlgStockEntry.DoModal();
}

void CAeApp::OnUpdateInformationenStockentry(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathDel()
{
    TRACE("OnHipathDel\n");
    m_AeTrace.WriteTrace("", "", "OnHipathDel\n");

    m_ProCenter.SetHiPathKndNr(0);
    m_ProCenter.SetHiPathVzNr(0);
    ::PostMessage(
        ((CFrameWndMultiLang*)m_pMainWnd)->GetActiveView()->GetSafeHwnd(),
        WM_RENEW,0,0);
}

void CAeApp::OnUpdateHipathDel(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathDel\n");

    if (!m_pAeUser->IsHiPathUser())
        pCmdUI->Enable(FALSE);
    else if (m_ProCenter.GetHiPathKndNr() == 0)
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnPflegeBackrouting()
{
    CDBackRouting dlgBackRouting;
    dlgBackRouting.DoModal();
}

void CAeApp::OnUpdatePflegeBackrouting(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnHipathRoutback()
{
    TRACE("OnHipathRoutback\n");
    m_AeTrace.WriteTrace("", "", "OnHipathRoutback\n");

    CDRoutBack dlgRoutBack;
    dlgRoutBack.DoModal();
}

void CAeApp::OnUpdateHipathRoutback(CCmdUI* pCmdUI)
{
    //TRACE("OnUpdateHipathRoutback\n");

    if (m_ProCenter.GetHiPathVzNr() == 0)
        pCmdUI->Enable(FALSE);
}

void CAeApp::OnExtrasNureigenerufe()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NUREIGENERUFE, MF_BYCOMMAND) == MF_CHECKED)
        IsAnrufPlanEigen = false; //check war vorher !!!
    else
        IsAnrufPlanEigen = true;
}

void CAeApp::OnUpdateExtrasNureigenerufe(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsAnrufPlanEigen() ? 1 : 0);
    }
}

bool CAeApp::IsKABAKomb(short sVZ, CString cAufArt, CString cKA, CString cBA)
{
    return _presenter.IsKABAKomb(sVZ, cAufArt, cKA, cBA);
}

void CAeApp::OnSortzurorderKdklasse()
{
    OrderSort = SORT_ORDER_KDKLASSE;
}

void CAeApp::OnUpdateSortzurorderKdklasse(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_KDKLASSE)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnKundeAuftragseingangsPruefung()
{
    DCustomerOrderCheck dlgCustomerOrderCheck;
    dlgCustomerOrderCheck.DoModal();
}

void CAeApp::OnUpdateKundeAuftragseingangsPruefung(CCmdUI* /*pCmdUI*/)
{
}

int CAeApp::GetKoArtenListeVZ(short sVZ, int index, CString& KoArt)
{
    return _presenter.GetKoArtenListeVZ(sVZ, index, KoArt);
}

void CAeApp::GetBranchName(short sVZ, CString& BranchName)
{
    _presenter.GetBranchName(sVZ, BranchName);
}

void CAeApp::GetRemarkTypes(short sRemarktype, CString& RemarkName)
{
    _presenter.GetRemarkTypes(sRemarktype, RemarkName);
}

int CAeApp::GetBuArtenListeVZ(short sVZ, int index, CString& BuArt)
{
    return _presenter.GetBuArtenListeVZ(sVZ, index, BuArt);
}

int CAeApp::GetTaxRates(int index, char& cStd, double& TaxRate)
{
    return _presenter.GetTaxRates(index, cStd, TaxRate);
}

void CAeApp::OnSortzurorderPos()
{
    OrderSort = SORT_ORDER_ANZPOS;
}

void CAeApp::OnUpdateSortzurorderPos(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_ANZPOS)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnSortzurorderBranchno()
{
    OrderSort = SORT_ORDER_BRANCHNO;
}

void CAeApp::OnUpdateSortzurorderBranchno(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        if (OrderSort() == SORT_ORDER_BRANCHNO)
            pCmdUI->SetRadio();
        else
            pCmdUI->SetCheck(0);
    }
}

void CAeApp::OnExtrasRabatt()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_RABATT, MF_BYCOMMAND) == MF_CHECKED)
    {
        IsAnzRabatte = false;   //check war vorher !!!
    }
    else
    {
        IsAnzRabatte = true;
    }
    ((CAeFView *)m_pViewEing)->ChangeColumnText();
}

void CAeApp::OnUpdateExtrasRabatt(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsAnzRabatte() ? 1 : 0);
    }
}

void CAeApp::OnExtrasUebergehenva10()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_UEBERGEHENVA10, MF_BYCOMMAND) == MF_CHECKED)
        IsNoVA10 = false;  //check war vorher !!!
    else
        IsNoVA10 = true;
}

void CAeApp::OnUpdateExtrasUebergehenva10(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsNoVA10() ? 1 : 0);
    }
}

void CAeApp::OnInformationenDealerUmsatz()
{
    CDDealerUmsatz dlgDealerUmsatz;
    dlgDealerUmsatz.DoModal();
}

void CAeApp::OnUpdateInformationenDealerUmsatz(CCmdUI* pCmdUI)
{
    if (!IsBG())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeApp::ClearZUGrund(int ZUGrund)
{
    CAUFTRAG auftrag;
    memset(auftrag.s.ZUGRUND,'1',L_AUFTRAG_ZUGRUND);
    auftrag.s.ZUGRUND[ZUGrund] = '0';
    auftrag.Server(AasrvClearZU, PIPE_AE_SRV);
}

void CAeApp::OnExtrasNuraktiveartikelinf11()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NURAKTIVEARTIKELINF11, MF_BYCOMMAND) == MF_CHECKED)
        IsNurAktF11 = false;    //check war vorher !!!
    else
        IsNurAktF11 = true;
}

void CAeApp::OnUpdateExtrasNuraktiveartikelinf11(CCmdUI* pCmdUI)
{
    if (IsBG())
    {
        pCmdUI->SetCheck(IsNurAktF11() ? 1 : 0);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeApp::OnExtrasNobatch()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NOBATCH, MF_BYCOMMAND) == MF_CHECKED)
        IsNoBatch = false;    //check war vorher !!!
    else
        IsNoBatch = true;
}

void CAeApp::OnUpdateExtrasNobatch(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsNoBatch() ? 1 : 0);
    }
}

void CAeApp::OnExtrasNoPromo()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NO_PROMO, MF_BYCOMMAND) == MF_CHECKED)
        IsNoPromo = false;   //check war vorher !!!
    else
        IsNoPromo = true;
}

void CAeApp::OnUpdateExtrasNoPromo(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsNoPromo() ? 1 : 0);
    }
}

void CAeApp::OnExtrasNoKippzeit()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_NO_KIPPZEIT, MF_BYCOMMAND) == MF_CHECKED)
        IsNoKippzeit = false; //check war vorher !!!
    else
        IsNoKippzeit = true;
}

void CAeApp::OnUpdateExtrasNoKippzeit(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser() || IsBG())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsNoKippzeit() ? 1 : 0);
    }
}

void CAeApp::OnIbtbranchUpd()
{
    CDIbtBranches dlgIbtBranches;
    dlgIbtBranches.m_bNLevelIBT = TRUE;
    dlgIbtBranches.DoModal();
}

void CAeApp::OnUpdateIbtbranchUpd(CCmdUI* pCmdUI)
{
    if (IsDE())
    {
        if (!m_pAeUser->UpdAltfil())
            pCmdUI->Enable(FALSE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeApp::OnExtrasInfolisteFirstletter()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_INFOLISTE_FIRSTLETTER, MF_BYCOMMAND) == MF_CHECKED)
        IsFirstLetter = false;  //check war vorher !!!
    else
        IsFirstLetter = true;
}


void CAeApp::OnUpdateExtrasInfolisteFirstletter(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsFirstLetter() ? 1 : 0);
    }
}


void CAeApp::OnAuftragFcOrders()
{
    CFCOrders dlgFCOrders;
    if (dlgFCOrders.DoModal() == IDOK)
    {
        ((CAeFView *)m_pViewEing)->OpenOrder(dlgFCOrders.GetAufNr());
    }
}


void CAeApp::OnUpdateAuftragFcOrders(CCmdUI* pCmdUI)
{
    if (!IsBG())
    {
        pCmdUI->Enable(FALSE);
    }
}


void CAeApp::OnExtrasKommaNoTab()
{
    if (m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_KOMMA_NO_TAB, MF_BYCOMMAND) == MF_CHECKED)
        IsKommaNoTab = false;  //check war vorher !!!
    else
        IsKommaNoTab = true;
}


void CAeApp::OnUpdateExtrasKommaNoTab(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    else
    {
        pCmdUI->SetCheck(IsKommaNoTab() ? 1 : 0);
    }
}


void CAeApp::OnPflegeCsvimportparam()
{
    CDCSVFormat dlgCSVFormat;
    dlgCSVFormat.DoModal();
}


void CAeApp::OnUpdatePflegeCsvimportparam(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
        pCmdUI->Enable(FALSE);
    if (!m_pAeUser->IsPflegeCSVImportParam())
    {
        ModifyMenu(m_pMainWnd->GetMenu()->m_hMenu, pCmdUI->m_nID, MF_BYCOMMAND | MF_STRING, pCmdUI->m_nID, CResString::ex().getStrTblText(AETXT_ANZEIGE_CSV));
    }
}

void CAeApp::OnUpdatePflegeDeleteReservation(CCmdUI* pCmdUI)
{
    if (!m_pAeUser->IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
    if (!m_pAeUser->IsPflegeReserve())
    {
        pCmdUI->Enable(FALSE);
    }
}

const CCountry& CAeApp::GetCountry() const
{
    return _country;
}
