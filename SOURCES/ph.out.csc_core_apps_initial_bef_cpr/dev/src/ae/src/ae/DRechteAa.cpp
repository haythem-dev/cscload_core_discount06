// DRechteAa.cpp : implementation file
//

#include "stdafx.h"
#include "DRechteAa.h"

/////////////////////////////////////////////////////////////////////////////
// CDRechteAa dialog


CDRechteAa::CDRechteAa(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRechteAa::IDD, pParent)
    , m_bKreditAbschluss(FALSE)
    , m_bInternetAbschluss(FALSE)
    , m_bReserve(FALSE)
    , m_bBTMAbschluss(FALSE)
    , m_bCustGrpsAdmin(FALSE)
    , m_bNotfall(FALSE)
    , m_bCC(FALSE)
    , m_bRufweiter(FALSE)
    , m_bQuota(FALSE)
    , m_bDD(FALSE)
    , m_bBranchInfo(FALSE)
    , m_bForbidden(FALSE)
    , m_bSeporder(FALSE)
    , m_bVA(FALSE)
    , m_bFreePrice(FALSE)
    , m_bDiscountUp(FALSE)
    , m_bBeilageUp(FALSE)
    , m_bReserveZert(FALSE)
    , m_bReserveBPZ(FALSE)
    , m_bArzneiEH(FALSE)
    , m_bCheckKC(FALSE)
    , m_bUserInfoVz(FALSE)
    , m_bUserInfoAll(FALSE)
    , m_bDealerInfoAll(FALSE)
    , m_bEncloser(FALSE)
    , m_bOnlyInfo(FALSE)
    , m_bReserveCharge(FALSE)
    , m_bChangeRebateCalc(FALSE)
    , m_bDPODays(FALSE)
    , m_bMSV3bearb(FALSE)
    , m_bOriginTypeSettings(FALSE)
    , m_bCremaMailAdr(FALSE)
    , m_bCremaStorno(FALSE)
    , m_bMSV3bearbNo(FALSE)
    , m_b2ndLevel(FALSE)
    , m_bCBRemarks(FALSE)
    , m_bCstTours(FALSE)
    , m_bExtraTourReasons(FALSE)
    , m_bBestellFenster(FALSE)
    , m_bCremaChangeTour(FALSE)
    , m_bReservationConfig(FALSE)
    , m_bCSVFormate(FALSE)
    , m_bCSVImport(FALSE)
    , m_bDEGetter(FALSE)
    , m_bAnzLief(FALSE)
    , m_bAnzRech(FALSE)
    , m_bWerbeFach(FALSE)
    , m_bAnzParamChange(FALSE)
{
    m_bAdmin = FALSE;
    m_bAndFil = FALSE;
    m_bKndInf = FALSE;
    m_bParAufArt = FALSE;
    m_bParAufBearb = FALSE;
    m_bParAufErg = FALSE;
    m_bParBuchArt = FALSE;
    m_bParKaBaKomb = FALSE;
    m_bParKoBehTyp = FALSE;
    m_bParKommi = FALSE;
    m_bParKommiArt = FALSE;
    m_bParKondGr = FALSE;
    m_bParNachArt = FALSE;
    m_bUpdUser = FALSE;
    m_bUser = FALSE;
    m_CUser = _T("");
    m_CVergUser = _T("");
    m_bUpdTour = FALSE;
    m_bUpdInfo = FALSE;
    m_bUpdZeitart = FALSE;
    m_bUpdAltfil = FALSE;
    m_bUpdEntsperr = FALSE;
    m_bRufpAbw = FALSE;
    m_bKndAart = FALSE;
    m_bKndFiliUms = FALSE;
    m_bPlanteil = FALSE;
    m_bCallback = FALSE;
    m_bChangeFiliale = FALSE;
    m_bStatusErl = FALSE;
    m_bSeraPlan = FALSE;
    m_bAufAnz = FALSE;
    m_bSperreAe = FALSE;
    m_bNurInfo = FALSE;
    m_bMailUser = FALSE;
    m_bMessage = FALSE;
    m_bUpdModem = FALSE;
    m_bMehrVz = FALSE;
    m_bAnrufplan = FALSE;
    m_bUpdRegion = FALSE;
    m_bFeiertage = FALSE;
    m_bBewegungen = FALSE;
    m_bKeinPlan = FALSE;
    m_bDispobearb = FALSE;
    m_bDisporechte = FALSE;
    m_bDispodoku = FALSE;
    m_bDispoHinttext = FALSE;
    m_bHiPath = FALSE;
    m_csAgentId = _T("");
    m_bInfoPflege = FALSE;
}


void CDRechteAa::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_INFO_PFLEGE, m_CBInfoPflege);
    DDX_Control(pDX, IDC_EDIT_AGENTID, m_edit_AgentId);
    DDX_Control(pDX, IDC_AE_HIPATH, m_CBHiPath);
    DDX_Control(pDX, IDC_AE_DISPO_DOKU, m_CBDispodoku);
    DDX_Control(pDX, IDC_AE_DISPO_RECHTE, m_CBDisporechte);
    DDX_Control(pDX, IDC_AE_DISPO_BEARB, m_CBDispobearb);
    DDX_Control(pDX, IDC_CHECK_KEIN_PLAN, m_CBKeinPlan);
    DDX_Control(pDX, IDC_AE_BEWEGUNGEN, m_CBBewegungen);
    DDX_Control(pDX, IDC_AE_FEIERTAGE, m_CBFeiertage);
    DDX_Control(pDX, IDC_AE_UPD_REGION, m_CBUpdRegion);
    DDX_Control(pDX, IDC_AE_ANRUFPLAN, m_CBAnrufplan);
    DDX_Control(pDX, IDC_AE_MEHR_VZ, m_CBMehrVz);
    DDX_Control(pDX, IDC_AE_UPD_MODEM, m_CBUpdModem);
    DDX_Control(pDX, IDC_CHECK_MESSAGE, m_CBMessage);
    DDX_Control(pDX, IDC_CHECK_MAIL_USER, m_CBMailUser);
    DDX_Control(pDX, IDC_AE_NUR_INFO, m_CBNurInfo);
    DDX_Control(pDX, IDC_AE_SPERRE_AE, m_CBSperreAe);
    DDX_Control(pDX, IDC_AE_AUF_ANZ, m_CBAufAnz);
    DDX_Control(pDX, IDC_AE_SERA_PLAN, m_mCBSeraPlan);
    DDX_Control(pDX, IDC_AE_STATUS_ERL, m_CBStatusErl);
    DDX_Control(pDX, IDC_CHECK_CHANGE_FILIALE, m_CBChangeFiliale);
    DDX_Control(pDX, IDC_AE_CALLBACK, m_CBCallback);
    DDX_Control(pDX, IDC_AE_PLANTEIL, m_CBPlanteil);
    DDX_Control(pDX, IDC_AE_KND_FILI_UMS, m_CBKndFiliUms);
    DDX_Control(pDX, IDC_AE_KND_AART, m_CBKndAart);
    DDX_Control(pDX, IDC_AE_RUFP_ABW, m_CBRufpAbw);
    DDX_Control(pDX, IDC_AE_ENTSPERR, m_CBUpdEntsperr);
    DDX_Control(pDX, IDC_AE_ALTFILIALE, m_CBUpdAltfil);
    DDX_Control(pDX, IDC_AE_ZEITART, m_CBUpdZeitart);
    DDX_Control(pDX, IDC_AE_UPDINFO, m_CBUpdInfo);
    DDX_Control(pDX, IDC_AE_UPDTOUR, m_CBUpdtour);
    DDX_Control(pDX, IDC_AE_ANDERE_FILIALE, m_CBAndFil);
    DDX_Control(pDX, IDC_AE_KUNDENINFO, m_CDKndInf);
    DDX_Control(pDX, IDC_AE_PAR_AUFART, m_CDParAufArt);
    DDX_Control(pDX, IDC_AE_PAR_AUFBEARB, m_CDParAufBearb);
    DDX_Control(pDX, IDC_AE_PAR_AUFERG, m_CDParAufErg);
    DDX_Control(pDX, IDC_AE_PAR_BUCHART, m_CDParBuchArt);
    DDX_Control(pDX, IDC_AE_PAR_KABAKOMB, m_CDParKaBaKomb);
    DDX_Control(pDX, IDC_AE_PAR_KOMMI, m_CDParKommi);
    DDX_Control(pDX, IDC_AE_PAR_KOBEHTYP, m_CDParKoBehTyp);
    DDX_Control(pDX, IDC_AE_PAR_KOMMIART, m_CDParKommiArt);
    DDX_Control(pDX, IDC_AE_PAR_KONDGR, m_CDParKondGr);
    DDX_Control(pDX, IDC_AE_PAR_NACHART, m_CBParNachArt);
    DDX_Control(pDX, IDC_AE_UPDUSER, m_CBUPdUser);
    DDX_Control(pDX, IDC_AE_USER, m_CBUser);
    DDX_Control(pDX, IDC_AE_ADMIN, m_CBAdmin);
    DDX_Check(pDX, IDC_AE_ADMIN, m_bAdmin);
    DDX_Check(pDX, IDC_AE_ANDERE_FILIALE, m_bAndFil);
    DDX_Check(pDX, IDC_AE_KUNDENINFO, m_bKndInf);
    DDX_Check(pDX, IDC_AE_PAR_AUFART, m_bParAufArt);
    DDX_Check(pDX, IDC_AE_PAR_AUFBEARB, m_bParAufBearb);
    DDX_Check(pDX, IDC_AE_PAR_AUFERG, m_bParAufErg);
    DDX_Check(pDX, IDC_AE_PAR_BUCHART, m_bParBuchArt);
    DDX_Check(pDX, IDC_AE_PAR_KABAKOMB, m_bParKaBaKomb);
    DDX_Check(pDX, IDC_AE_PAR_KOBEHTYP, m_bParKoBehTyp);
    DDX_Check(pDX, IDC_AE_PAR_KOMMI, m_bParKommi);
    DDX_Check(pDX, IDC_AE_PAR_KOMMIART, m_bParKommiArt);
    DDX_Check(pDX, IDC_AE_PAR_KONDGR, m_bParKondGr);
    DDX_Check(pDX, IDC_AE_PAR_NACHART, m_bParNachArt);
    DDX_Check(pDX, IDC_AE_UPDUSER, m_bUpdUser);
    DDX_Check(pDX, IDC_AE_USER, m_bUser);
    DDX_Text(pDX, IDC_USER, m_CUser);
    DDX_Text(pDX, IDC_VERGUSER, m_CVergUser);
    DDX_Check(pDX, IDC_AE_UPDTOUR, m_bUpdTour);
    DDX_Check(pDX, IDC_AE_UPDINFO, m_bUpdInfo);
    DDX_Check(pDX, IDC_AE_ZEITART, m_bUpdZeitart);
    DDX_Check(pDX, IDC_AE_ALTFILIALE, m_bUpdAltfil);
    DDX_Check(pDX, IDC_AE_ENTSPERR, m_bUpdEntsperr);
    DDX_Check(pDX, IDC_AE_RUFP_ABW, m_bRufpAbw);
    DDX_Check(pDX, IDC_AE_KND_AART, m_bKndAart);
    DDX_Check(pDX, IDC_AE_KND_FILI_UMS, m_bKndFiliUms);
    DDX_Check(pDX, IDC_AE_PLANTEIL, m_bPlanteil);
    DDX_Check(pDX, IDC_AE_CALLBACK, m_bCallback);
    DDX_Check(pDX, IDC_CHECK_CHANGE_FILIALE, m_bChangeFiliale);
    DDX_Check(pDX, IDC_AE_STATUS_ERL, m_bStatusErl);
    DDX_Check(pDX, IDC_AE_SERA_PLAN, m_bSeraPlan);
    DDX_Check(pDX, IDC_AE_AUF_ANZ, m_bAufAnz);
    DDX_Check(pDX, IDC_AE_SPERRE_AE, m_bSperreAe);
    DDX_Check(pDX, IDC_AE_NUR_INFO, m_bNurInfo);
    DDX_Check(pDX, IDC_CHECK_MAIL_USER, m_bMailUser);
    DDX_Check(pDX, IDC_CHECK_MESSAGE, m_bMessage);
    DDX_Check(pDX, IDC_AE_UPD_MODEM, m_bUpdModem);
    DDX_Check(pDX, IDC_AE_MEHR_VZ, m_bMehrVz);
    DDX_Check(pDX, IDC_AE_ANRUFPLAN, m_bAnrufplan);
    DDX_Check(pDX, IDC_AE_UPD_REGION, m_bUpdRegion);
    DDX_Check(pDX, IDC_AE_FEIERTAGE, m_bFeiertage);
    DDX_Check(pDX, IDC_AE_BEWEGUNGEN, m_bBewegungen);
    DDX_Check(pDX, IDC_CHECK_KEIN_PLAN, m_bKeinPlan);
    DDX_Check(pDX, IDC_AE_DISPO_BEARB, m_bDispobearb);
    DDX_Check(pDX, IDC_AE_DISPO_RECHTE, m_bDisporechte);
    DDX_Check(pDX, IDC_AE_DISPO_DOKU, m_bDispodoku);
    DDX_Check(pDX, IDC_AE_DISPO_HINTTEXT, m_bDispoHinttext);
    DDX_Check(pDX, IDC_AE_HIPATH, m_bHiPath);
    DDX_Text(pDX, IDC_EDIT_AGENTID, m_csAgentId);
    DDX_Check(pDX, IDC_CHECK_INFO_PFLEGE, m_bInfoPflege);
    DDX_Control(pDX, IDC_AE_VORAUS, m_CBVoraus);
    DDX_Check(pDX, IDC_AE_VORAUS, m_bVoraus);
    DDX_Check(pDX, IDC_AE_KREDIT_ABSCHLUSS, m_bKreditAbschluss);
    DDX_Check(pDX, IDC_AE_INTERNET_ABSCHLUSS, m_bInternetAbschluss);
    DDX_Check(pDX, IDC_AE_RESERVE, m_bReserve);
    DDX_Check(pDX, IDC_AE_BTM_ABSCHLUSS, m_bBTMAbschluss);
    DDX_Check(pDX, IDC_CHK_CUSTGRPS4COLLORDER, m_bCustGrpsAdmin);
    DDX_Check(pDX, IDC_CHECK_NOTFALL, m_bNotfall);
    DDX_Check(pDX, IDC_CHECK_COUNTRY, m_bCC);
    DDX_Check(pDX, IDC_CHECK_RUFWEITER, m_bRufweiter);
    DDX_Check(pDX, IDC_CHECK_QUOTA, m_bQuota);
    DDX_Check(pDX, IDC_CHECK_DD, m_bDD);
    DDX_Check(pDX, IDC_CHECK_BRANCHINFO, m_bBranchInfo);
    DDX_Check(pDX, IDC_CHECK_FORBIDDEN, m_bForbidden);
    DDX_Check(pDX, IDC_CHECK_SEPORDER, m_bSeporder);
    DDX_Check(pDX, IDC_CHECK_VA, m_bVA);
    DDX_Check(pDX, IDC_CHECK_FREE_PRICE, m_bFreePrice);
    DDX_Check(pDX, IDC_CHECK_DISCOUNT_UP, m_bDiscountUp);
    DDX_Control(pDX, IDC_COMBO_POOL, m_CComboBoxPool);
    DDX_Check(pDX, IDC_CHECK_BEILAGE_UP, m_bBeilageUp);
    DDX_Check(pDX, IDC_CHECK_RESERVE_ZERT, m_bReserveZert);
    DDX_Check(pDX, IDC_CHECK_RESERVE_BPZ, m_bReserveBPZ);
    DDX_Check(pDX, IDC_CHECK_ARZNEI_EH, m_bArzneiEH);
    DDX_Check(pDX, IDC_CHECK_KOMMI_CHANGE, m_bCheckKC);
    DDX_Check(pDX, IDC_CHECK_USER_INFO_VZ, m_bUserInfoVz);
    DDX_Check(pDX, IDC_CHECK_USER_INFO_ALLE, m_bUserInfoAll);
    DDX_Check(pDX, IDC_CHECK_DEALER_INFO_ALLE, m_bDealerInfoAll);
    DDX_Check(pDX, IDC_CHECK_ENCLOSER, m_bEncloser);
    DDX_Check(pDX, IDC_CHECK_NUR_INFO, m_bOnlyInfo);
    DDX_Check(pDX, IDC_CHECK_RESERVE_CHARGE, m_bReserveCharge);
    DDX_Check(pDX, IDC_CHECK_CHANGE_REBATE_CALC, m_bChangeRebateCalc);
    DDX_Check(pDX, IDC_CHECK_DPODAYS, m_bDPODays);
    DDX_Check(pDX, IDC_AE_MSV3_BEARB, m_bMSV3bearb);
    DDX_Control(pDX, IDC_CHECK_ORIGINTYPESETTINGS, m_CBOriginTypeSettings);
    DDX_Check(pDX, IDC_CHECK_ORIGINTYPESETTINGS, m_bOriginTypeSettings);
    DDX_Check(pDX, IDC_CHECK_CREMA_MAIL_ADR, m_bCremaMailAdr);
    DDX_Check(pDX, IDC_CHECK_CREMA_STORNO, m_bCremaStorno);
    DDX_Check(pDX, IDC_AE_MSV3_BEARB_NO, m_bMSV3bearbNo);
    DDX_Check(pDX, IDC_CHECK_2ND_LEVEL, m_b2ndLevel);
    DDX_Check(pDX, IDC_CHECK_CB_REMARKS, m_bCBRemarks);
    DDX_Check(pDX, IDC_CHECK_CST_TOURS, m_bCstTours);
    DDX_Check(pDX, IDC_CHECK_EXTRA_TOUR_REASONS, m_bExtraTourReasons);
    DDX_Check(pDX, IDC_CHECK_BESTELL_FENSTER, m_bBestellFenster);
    DDX_Check(pDX, IDC_CHECK_CREMA_CHANGE_TOUR, m_bCremaChangeTour);
    DDX_Check(pDX, IDC_CHECK_RESERVATION_CONFIG, m_bReservationConfig);
    DDX_Control(pDX, IDC_CHECK_PFLEGE_CSVIMPORT, m_CBCSVFormate);
    DDX_Check(pDX, IDC_CHECK_PFLEGE_CSVIMPORT, m_bCSVFormate);
    DDX_Control(pDX, IDC_CHECK_IMPORT_CSV_AUFTRAG, m_CBCSVImport);
    DDX_Check(pDX, IDC_CHECK_IMPORT_CSV_AUFTRAG, m_bCSVImport);
    DDX_Control(pDX, IDC_CHECK_DE_GETTER, m_CBDEGetter);
    DDX_Check(pDX, IDC_CHECK_DE_GETTER, m_bDEGetter);
    DDX_Control(pDX, IDC_CHECK_CB_REMARKS, m_CBCBRemarks);
    DDX_Control(pDX, IDC_CHECK_ANZ_LIEF, m_CBAnzLief);
    DDX_Check(pDX, IDC_CHECK_ANZ_LIEF, m_bAnzLief);
    DDX_Control(pDX, IDC_CHECK_ANZ_RECH, m_CBAnzRech);
    DDX_Check(pDX, IDC_CHECK_ANZ_RECH, m_bAnzRech);
    DDX_Control(pDX, IDC_AE_PAR_WERBEFACH, m_CBWerbeFach);
    DDX_Check(pDX, IDC_AE_PAR_WERBEFACH, m_bWerbeFach);
    DDX_Control(pDX, IDC_CHECK_ANZ_PARAM_CHANGES, m_CBAnzParamChange);
    DDX_Check(pDX, IDC_CHECK_ANZ_PARAM_CHANGES, m_bAnzParamChange);
    DDX_Check(pDX, IDC_AE_CMI_BEARBEITEN, m_bChangeCMIOrder); //TODO DZ
}


BEGIN_MESSAGE_MAP(CDRechteAa, CDialogMultiLang)
    ON_BN_CLICKED(IDC_AE_ADMIN, OnAeAdmin)
    ON_BN_CLICKED(IDC_AE_ANDERE_FILIALE, OnAeAndereFiliale)
    ON_BN_CLICKED(IDC_AE_KUNDENINFO, OnAeKundeninfo)
    ON_BN_CLICKED(IDC_AE_PAR_AUFART, OnAeParAufart)
    ON_BN_CLICKED(IDC_AE_PAR_AUFBEARB, OnAeParAufbearb)
    ON_BN_CLICKED(IDC_AE_PAR_AUFERG, OnAeParAuferg)
    ON_BN_CLICKED(IDC_AE_PAR_BUCHART, OnAeParBuchart)
    ON_BN_CLICKED(IDC_AE_PAR_KABAKOMB, OnAeParKabakomb)
    ON_BN_CLICKED(IDC_AE_PAR_KOBEHTYP, OnAeParKobehtyp)
    ON_BN_CLICKED(IDC_AE_PAR_KOMMI, OnAeParKommi)
    ON_BN_CLICKED(IDC_AE_PAR_KOMMIART, OnAeParKommiart)
    ON_BN_CLICKED(IDC_AE_PAR_KONDGR, OnAeParKondgr)
    ON_BN_CLICKED(IDC_AE_PAR_NACHART, OnAeParNachart)
    ON_BN_CLICKED(IDC_AE_UPDUSER, OnAeUpduser)
    ON_BN_CLICKED(IDC_AE_USER, OnAeUser)
    ON_BN_CLICKED(IDC_AE_UPDINFO, OnAeUpdinfo)
    ON_BN_CLICKED(IDC_AE_ZEITART, OnAeZeitart)
    ON_BN_CLICKED(IDC_AE_ALTFILIALE, OnAeAltfiliale)
    ON_BN_CLICKED(IDC_AE_ENTSPERR, OnAeEntsperr)
    ON_BN_CLICKED(IDC_AE_RUFP_ABW, OnAeRufpAbw)
    ON_BN_CLICKED(IDC_AE_KND_AART, OnAeKndAart)
    ON_BN_CLICKED(IDC_AE_KND_FILI_UMS, OnAeKndFiliUms)
    ON_BN_CLICKED(IDC_AE_PLANTEIL, OnAePlanteil)
    ON_BN_CLICKED(IDC_AE_CALLBACK, OnAeCallback)
    ON_BN_CLICKED(IDC_CHECK_CHANGE_FILIALE, OnCheckChangeFiliale)
    ON_BN_CLICKED(IDC_AE_STATUS_ERL, OnAeStatusErl)
    ON_BN_CLICKED(IDC_AE_SERA_PLAN, OnAeSeraPlan)
    ON_BN_CLICKED(IDC_AE_AUF_ANZ, OnAeAufAnz)
    ON_BN_CLICKED(IDC_AE_SPERRE_AE, OnAeSperreAe)
    ON_BN_CLICKED(IDC_AE_NUR_INFO, OnAeNurInfo)
    ON_BN_CLICKED(IDC_CHECK_MAIL_USER, OnCheckMailUser)
    ON_BN_CLICKED(IDC_CHECK_MESSAGE, OnCheckMessage)
    ON_BN_CLICKED(IDC_AE_UPD_MODEM, OnAeUpdModem)
    ON_BN_CLICKED(IDC_AE_MEHR_VZ, OnAeMehrVz)
    ON_BN_CLICKED(IDC_AE_ANRUFPLAN, OnAeAnrufplan)
    ON_BN_CLICKED(IDC_AE_UPD_REGION, OnAeUpdRegion)
    ON_BN_CLICKED(IDC_AE_FEIERTAGE, OnAeFeiertage)
    ON_BN_CLICKED(IDC_AE_BEWEGUNGEN, OnAeBewegungen)
    ON_BN_CLICKED(IDC_CHECK_KEIN_PLAN, OnCheckKeinPlan)
    ON_BN_CLICKED(IDC_AE_DISPO_BEARB, OnAeDispoBearb)
    ON_BN_CLICKED(IDC_AE_DISPO_RECHTE, OnAeDispoRechte)
    ON_BN_CLICKED(IDC_AE_DISPO_DOKU, OnAeDispoDoku)
    ON_BN_CLICKED(IDC_AE_HIPATH, OnAeHipath)
    ON_EN_CHANGE(IDC_EDIT_AGENTID, OnChangeEditAgentid)
    ON_BN_CLICKED(IDC_CHECK_INFO_PFLEGE, OnCheckInfoPflege)
    ON_BN_CLICKED(IDC_AE_VORAUS, OnBnClickedAeVoraus)
    ON_BN_CLICKED(IDC_AE_KREDIT_ABSCHLUSS, OnBnClickedAeKreditAbschluss)
    ON_BN_CLICKED(IDC_AE_INTERNET_ABSCHLUSS, OnBnClickedAeInternetAbschluss)
    ON_BN_CLICKED(IDC_AE_RESERVE, OnBnClickedAeReserve)
    ON_BN_CLICKED(IDC_AE_BTM_ABSCHLUSS, OnBnClickedAeBtmAbschluss)
    ON_BN_CLICKED(IDC_CHK_CUSTGRPS4COLLORDER, OnBnClickedChkCustgrps4collorder)
    ON_BN_CLICKED(IDC_CHECK_NOTFALL, OnBnClickedCheckNotfall)
    ON_BN_CLICKED(IDC_CHECK_COUNTRY, OnBnClickedCheckCountry)
    ON_BN_CLICKED(IDC_CHECK_RUFWEITER, OnBnClickedCheckRufweiter)
    ON_BN_CLICKED(IDC_CHECK_QUOTA, OnBnClickedCheckQuota)
    ON_BN_CLICKED(IDC_CHECK_DD, OnBnClickedCheckDd)
    ON_BN_CLICKED(IDC_CHECK_BRANCHINFO, OnBnClickedCheckBranchinfo)
    ON_BN_CLICKED(IDC_CHECK_FORBIDDEN, OnBnClickedCheckForbidden)
    ON_BN_CLICKED(IDC_CHECK_SEPORDER, OnBnClickedCheckSeporder)
    ON_BN_CLICKED(IDC_CHECK_VA, OnBnClickedCheckVa)
    ON_BN_CLICKED(IDC_CHECK_FREE_PRICE, OnBnClickedCheckFreePrice)
    ON_BN_CLICKED(IDC_CHECK_DISCOUNT_UP, OnBnClickedCheckDiscountUp)
    ON_BN_CLICKED(IDC_CHECK_BEILAGE_UP, OnBnClickedCheckBeilageUp)
    ON_BN_CLICKED(IDC_CHECK_RESERVE_ZERT, OnBnClickedAeReserveZert)
    ON_BN_CLICKED(IDC_CHECK_RESERVE_BPZ, OnBnClickedAeReserveBPZ)
    ON_BN_CLICKED(IDC_CHECK_ARZNEI_EH, OnBnClickedArzneiEH)
    ON_BN_CLICKED(IDC_CHECK_KOMMI_CHANGE, OnBnClickedCheckKC)
    ON_BN_CLICKED(IDC_CHECK_USER_INFO_VZ, OnBnClickedUserInfoVz)
    ON_BN_CLICKED(IDC_CHECK_USER_INFO_ALLE, OnBnClickedUserInfoAll)
    ON_BN_CLICKED(IDC_CHECK_DEALER_INFO_ALLE, OnBnClickedCheckDealerInfoAlle)
    ON_BN_CLICKED(IDC_CHECK_ENCLOSER, OnBnClickedCheckEncloser)
    ON_BN_CLICKED(IDC_CHECK_NUR_INFO, OnBnClickedCheckNurInfo)
    ON_BN_CLICKED(IDC_CHECK_RESERVE_CHARGE, OnBnClickedCheckReserveCharge)
    ON_BN_CLICKED(IDC_CHECK_CHANGE_REBATE_CALC, OnBnClickedCheckChangeRebateCalc)
    ON_BN_CLICKED(IDC_CHECK_DPODAYS, OnBnClickedCheckDpodays)
    ON_BN_CLICKED(IDC_AE_MSV3_BEARB, OnBnClickedAeMsv3Bearb)
    ON_BN_CLICKED(IDC_CHECK_ORIGINTYPESETTINGS, OnBnClickedCheckOrigintypesettings)
    ON_BN_CLICKED(IDC_CHECK_CREMA_MAIL_ADR, &CDRechteAa::OnBnClickedCheckCremaMailAdr)
    ON_BN_CLICKED(IDC_CHECK_CREMA_STORNO, &CDRechteAa::OnBnClickedCheckCremaStorno)
    ON_BN_CLICKED(IDC_AE_MSV3_BEARB_NO, &CDRechteAa::OnBnClickedAeMsv3BearbNo)
    ON_BN_CLICKED(IDC_CHECK_2ND_LEVEL, &CDRechteAa::OnBnClickedCheck2ndLevel)
    ON_BN_CLICKED(IDC_CHECK_CB_REMARKS, &CDRechteAa::OnBnClickedCBRemarks)
    ON_BN_CLICKED(IDC_CHECK_CST_TOURS, &CDRechteAa::OnBnClickedCstTours)
    ON_BN_CLICKED(IDC_CHECK_EXTRA_TOUR_REASONS, &CDRechteAa::OnBnClickedExtraTourReasons)
    ON_BN_CLICKED(IDC_CHECK_BESTELL_FENSTER, &CDRechteAa::OnBnClickedBestellFenster)
    ON_BN_CLICKED(IDC_CHECK_CREMA_CHANGE_TOUR, &CDRechteAa::OnBnClickedCremaChangeTour)
    ON_BN_CLICKED(IDC_CHECK_RESERVATION_CONFIG, &CDRechteAa::OnBnClickedCheckReservationConfig)
    ON_BN_CLICKED(IDC_CHECK_PFLEGE_CSVIMPORT, &CDRechteAa::OnBnClickedCheckPflegeCsvimport)
    ON_BN_CLICKED(IDC_CHECK_IMPORT_CSV_AUFTRAG, &CDRechteAa::OnBnClickedCheckImportCsvAuftrag)
    ON_BN_CLICKED(IDC_CHECK_DE_GETTER, &CDRechteAa::OnBnClickedCheckDeGetter)
    ON_BN_CLICKED(IDC_CHECK_ANZ_LIEF, &CDRechteAa::OnBnClickedCheckAnzLief)
    ON_BN_CLICKED(IDC_CHECK_ANZ_RECH, &CDRechteAa::OnBnClickedCheckAnzRech)
    ON_BN_CLICKED(IDC_AE_PAR_WERBEFACH, &CDRechteAa::OnBnClickedAeParWerbefach)
    ON_BN_CLICKED(IDC_CHECK_ANZ_PARAM_CHANGES, &CDRechteAa::OnBnClickedCheckAnzParamChanges)
    ON_BN_CLICKED(IDC_AE_CMI_BEARBEITEN, &CDRechteAa::OnBnClickedChangeCMIOrder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRechteAa message handlers

BOOL CDRechteAa::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    CString cs;

    for (int j = 0; j < 99; j++)
    {
        cs.Format("%02d", j);
        m_CComboBoxPool.AddString(cs);
    }

    if (AeGetApp()->IsDE()) //in DE Keine Vorbelegung mehr erlaubt
    {
        GetDlgItem(IDC_STATIC_PRE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PRE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PRE_RAHMEN)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PRE_RAHMEN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_VERGUSER)->EnableWindow(FALSE);
        GetDlgItem(IDC_VERGUSER)->ShowWindow(SW_HIDE);
    }


    CAeUser& currentAeUser = GetAeUser();  //aktueller User
    m_CUser = m_User.GetUserName();
    m_csAgentId = m_User.GetAgentID();
    m_CComboBoxPool.SetCurSel(m_User.GetPoolID());

    //   aktuelle Rechte setzen
    m_bAdmin = m_User.IsAdminAndereFiliale();
    m_bAndFil = m_User.IsErfasAndereFiliale();
    m_bKndInf = m_User.IsErwKndInfo();
    m_bParAufArt = m_User.UpdParAuftrArt();
    m_bParAufBearb = m_User.UpdParAufBearb();
    m_bParAufErg = m_User.UpdParAufBeErg();
    m_bParBuchArt = m_User.UpdParBuchArt();
    m_bParKaBaKomb = m_User.UpdParKaBaKomb();
    m_bParKoBehTyp = m_User.UpdParKomBehTyp();
    m_bParKommi = m_User.UpdParKommi();
    m_bParKommiArt = m_User.UpdParKommArt();
    m_bParKondGr = m_User.UpdParKondGr();
    m_bParNachArt = m_User.UpdParNachrArten();
    m_bUpdUser = m_User.UpdUser();
    m_bUpdTour = m_User.UpdTour();
    m_bUser = m_User.IsAeUser();
    m_bUpdInfo = m_User.UpdInfo();
    m_bUpdAltfil = m_User.UpdAltfil();
    m_bUpdZeitart = m_User.UpdZeitart();
    m_bUpdEntsperr = m_User.UpdEntsperr();
    m_bRufpAbw = m_User.UpdRufpAbw();
    m_bKndAart = m_User.UpdKndAufArt();
    m_bKndFiliUms = m_User.AnzFilialUms();
    m_bPlanteil = m_User.Planteil();
    m_bCallback = m_User.UpdCallback();
    m_bChangeFiliale = m_User.ChangeFiliale();
    m_bStatusErl = m_User.StatusErl();
    m_bSeraPlan = m_User.UpdSeraPlan();
    m_bAufAnz = m_User.IsAnzAuf();
    m_bSperreAe = m_User.IsSperreAe();
    m_bNurInfo = m_User.IsInfoListe();
    m_bMailUser = m_User.UpdMailUser();
    m_bMessage = m_User.IsMessage();
    m_bUpdModem = m_User.UpdModem();
    m_bMehrVz = m_User.IsMehrVz();
    m_bAnrufplan = m_User.Anrufplanuebernahme();
    m_bUpdRegion = m_User.Regionenverwalten();
    m_bFeiertage = m_User.Feiertage();
    m_bBewegungen = m_User.Bewegungen();
    m_bKeinPlan = m_User.KeinPlan();
    m_bDispobearb = m_User.DispoBearb();
    m_bDisporechte = m_User.DispoRechte();
    m_bDispodoku = m_User.DispoDoku();
    m_bDispoHinttext = m_User.DispoHinttext();
    m_bHiPath = m_User.IsHiPathUser();
    m_bInfoPflege = m_User.IsInfoPflege();
    m_bVoraus = m_User.IsVorausPflege();
    m_bKreditAbschluss = m_User.IsKreditAbschluss();
    m_bInternetAbschluss = m_User.IsInternetAbschluss();
    m_bReserve = m_User.IsPflegeReserve();
    m_bBTMAbschluss = m_User.IsAbschlussBTM();
    m_bCustGrpsAdmin = m_User.IsAdminCustGrps();
    m_bNotfall = m_User.IsPflegeNotfall();
    m_bCC = m_User.IsPflegeCountry();
    m_bRufweiter = m_User.IsPflegeRufweiter();
    m_bQuota = m_User.IsPflegeQuota();
    m_bDD = m_User.IsPflegeDD();
    m_bBranchInfo = m_User.IsPflegeBranchInfo();
    m_bForbidden = m_User.IsPflegeForbidden();
    m_bSeporder = m_User.IsPflegeSeparat();
    m_bVA = m_User.IsPflegeVAIdf();
    m_bFreePrice = m_User.IsFreePrice();
    m_bDiscountUp = m_User.IsDiscountUp();
    m_bBeilageUp = m_User.IsBeilageUp();
    m_bReserveZert = m_User.IsPflegeReserveZert();
    m_bReserveBPZ = m_User.IsPflegeReserveBPZ();
    m_bArzneiEH = m_User.IsEinzelhandelApo();
    m_bCheckKC = m_User.IsCheckPickingChange();
    m_bUserInfoVz = m_User.IsUserInfoVz();
    m_bUserInfoAll = m_User.IsUserInfoAll();
    m_bDealerInfoAll = m_User.IsDealerInfoAll();
    m_bEncloser = m_User.IsPflegeEncloser();
    m_bOnlyInfo = m_User.IsOnlyInfo();
    m_bReserveCharge = m_User.IsPflegeReserveCharge();
    m_bChangeRebateCalc = m_User.IsChangeRebateCalc();
    m_bDPODays = m_User.IsChangeDPODays();
    m_bMSV3bearb = m_User.IsMSV3bearb();
    m_bMSV3bearbNo = m_User.IsMSV3bearbNo();
    m_bOriginTypeSettings = m_User.IsPflegeOrigintypesettings();
    m_bCremaMailAdr = m_User.IsPflegeCremaMailAdr();
    m_bCremaStorno = m_User.IsStornoCremaOrder();
    m_bReservationConfig = m_User.IsPflegeReservationConfig();
    m_b2ndLevel = m_User.Is2ndLevel();
    m_bCBRemarks = m_User.IsPflegeCBRemarks();
    m_bCstTours = m_User.IsPflegeCstTours();
    m_bExtraTourReasons = m_User.IsPflegeExtraTourReasons();
    m_bBestellFenster = m_User.IsPflegeBestellFenster();
    m_bCremaChangeTour = m_User.IsCremaChangeTour();
    m_bCSVFormate = m_User.IsPflegeCSVImportParam();
    m_bCSVImport = m_User.IsCSVImport();
    m_bDEGetter = m_User.IsDEGetter();
    m_bAnzLief = m_User.IsAnzLief();
    m_bAnzRech = m_User.IsAnzRech();
    m_bWerbeFach = m_User.IsEnableWerbeFach();
    m_bAnzParamChange = m_User.IsShowParamChanges();
    m_bChangeCMIOrder = m_User.IsAbleToChangeCMIOrder(); //TODO DZ

    //   erlaubte Rechte setzen
    m_CBAdmin.EnableWindow(currentAeUser.IsAdminAndereFiliale());
    m_CBAdmin.EnableWindow(currentAeUser.IsErfasAndereFiliale());
    m_CDKndInf.EnableWindow(currentAeUser.IsErwKndInfo());
    m_CDParAufArt.EnableWindow(currentAeUser.UpdParAuftrArt());
    m_CDParAufBearb.EnableWindow(currentAeUser.UpdParAufBearb());
    m_CDParAufErg.EnableWindow(currentAeUser.UpdParAufBeErg());
    m_CDParBuchArt.EnableWindow(currentAeUser.UpdParBuchArt());
    m_CDParKaBaKomb.EnableWindow(currentAeUser.UpdParKaBaKomb());
    m_CDParKoBehTyp.EnableWindow(currentAeUser.UpdParKomBehTyp());
    m_CDParKommi.EnableWindow(currentAeUser.UpdParKommi());
    m_CDParKommiArt.EnableWindow(currentAeUser.UpdParKommArt());
    m_CDParKondGr.EnableWindow(currentAeUser.UpdParKondGr());
    m_CBParNachArt.EnableWindow(currentAeUser.UpdParNachrArten());
    m_CBUPdUser.EnableWindow(currentAeUser.UpdUser());
    m_CBUpdtour.EnableWindow(currentAeUser.UpdTour());
    m_CBUser.EnableWindow(currentAeUser.IsAeUser());
    m_CBUpdInfo.EnableWindow(currentAeUser.UpdInfo());
    m_CBUpdAltfil.EnableWindow(currentAeUser.UpdAltfil());
    m_CBUpdZeitart.EnableWindow(currentAeUser.UpdZeitart());
    m_CBUpdEntsperr.EnableWindow(currentAeUser.UpdEntsperr());
    m_CBRufpAbw.EnableWindow(currentAeUser.UpdRufpAbw());
    m_CBKndAart.EnableWindow(currentAeUser.UpdKndAufArt());
    m_CBKndFiliUms.EnableWindow(currentAeUser.AnzFilialUms());
    m_CBPlanteil.EnableWindow(currentAeUser.Planteil());
    m_CBCallback.EnableWindow(currentAeUser.UpdCallback());
    m_CBChangeFiliale.EnableWindow(currentAeUser.ChangeFiliale());
    m_CBStatusErl.EnableWindow(currentAeUser.StatusErl());
    m_mCBSeraPlan.EnableWindow(currentAeUser.UpdSeraPlan());
    m_CBAufAnz.EnableWindow(currentAeUser.IsAnzAuf());
    m_CBSperreAe.EnableWindow(currentAeUser.IsSperreAe());
    m_CBNurInfo.EnableWindow(currentAeUser.IsInfoListe());
    m_CBMailUser.EnableWindow(currentAeUser.UpdMailUser());
    m_CBMessage.EnableWindow(currentAeUser.IsMessage());
    m_CBUpdModem.EnableWindow(currentAeUser.UpdModem());
    m_CBMehrVz.EnableWindow(currentAeUser.IsMehrVz());
    m_CBAnrufplan.EnableWindow(currentAeUser.Anrufplanuebernahme());
    m_CBUpdRegion.EnableWindow(currentAeUser.Regionenverwalten());
    m_CBFeiertage.EnableWindow(currentAeUser.Feiertage());
    m_CBBewegungen.EnableWindow(currentAeUser.Bewegungen());
    m_CBKeinPlan.EnableWindow(!currentAeUser.KeinPlan());
    m_CBDispobearb.EnableWindow(currentAeUser.DispoBearb());
    m_CBDisporechte.EnableWindow(currentAeUser.DispoRechte());
    m_CBDispodoku.EnableWindow(currentAeUser.DispoDoku());
    m_CBHiPath.EnableWindow(currentAeUser.IsHiPathUser());
    m_CBInfoPflege.EnableWindow(currentAeUser.IsInfoPflege());
    m_CBVoraus.EnableWindow(currentAeUser.IsVorausPflege());

    GetDlgItem(IDC_AE_KREDIT_ABSCHLUSS)->EnableWindow(currentAeUser.IsKreditAbschluss());
    GetDlgItem(IDC_AE_INTERNET_ABSCHLUSS)->EnableWindow(currentAeUser.IsInternetAbschluss());
    GetDlgItem(IDC_AE_RESERVE)->EnableWindow(currentAeUser.IsPflegeReserve());
    GetDlgItem(IDC_AE_BTM_ABSCHLUSS)->EnableWindow(currentAeUser.IsAbschlussBTM());
    GetDlgItem(IDC_CHK_CUSTGRPS4COLLORDER)->EnableWindow(currentAeUser.IsAdminCustGrps());
    GetDlgItem(IDC_CHECK_NOTFALL)->EnableWindow(currentAeUser.IsPflegeNotfall());
    GetDlgItem(IDC_CHECK_COUNTRY)->EnableWindow(currentAeUser.IsPflegeCountry());
    GetDlgItem(IDC_CHECK_RUFWEITER)->EnableWindow(currentAeUser.IsPflegeRufweiter());
    GetDlgItem(IDC_CHECK_QUOTA)->EnableWindow(currentAeUser.IsPflegeQuota());
    GetDlgItem(IDC_CHECK_DD)->EnableWindow(currentAeUser.IsPflegeDD());
    GetDlgItem(IDC_CHECK_BRANCHINFO)->EnableWindow(currentAeUser.IsPflegeBranchInfo());
    GetDlgItem(IDC_CHECK_FORBIDDEN)->EnableWindow(currentAeUser.IsPflegeForbidden());
    GetDlgItem(IDC_CHECK_SEPORDER)->EnableWindow(currentAeUser.IsPflegeSeparat());
    GetDlgItem(IDC_CHECK_VA)->EnableWindow(currentAeUser.IsPflegeVAIdf());
    GetDlgItem(IDC_CHECK_FREE_PRICE)->EnableWindow(currentAeUser.IsFreePrice());
    GetDlgItem(IDC_CHECK_DISCOUNT_UP)->EnableWindow(currentAeUser.IsDiscountUp());
    GetDlgItem(IDC_CHECK_BEILAGE_UP)->EnableWindow(currentAeUser.IsBeilageUp());
    GetDlgItem(IDC_CHECK_RESERVE_ZERT)->EnableWindow(currentAeUser.IsPflegeReserveZert());
    GetDlgItem(IDC_CHECK_RESERVE_BPZ)->EnableWindow(currentAeUser.IsPflegeReserveBPZ());
    GetDlgItem(IDC_CHECK_ARZNEI_EH)->EnableWindow(currentAeUser.IsEinzelhandelApo());
    GetDlgItem(IDC_CHECK_USER_INFO_VZ)->EnableWindow(currentAeUser.IsUserInfoVz());
    GetDlgItem(IDC_CHECK_USER_INFO_ALLE)->EnableWindow(currentAeUser.IsUserInfoAll());
    GetDlgItem(IDC_CHECK_DEALER_INFO_ALLE)->EnableWindow(currentAeUser.IsDealerInfoAll());
    GetDlgItem(IDC_CHECK_ENCLOSER)->EnableWindow(currentAeUser.IsPflegeEncloser());
    GetDlgItem(IDC_CHECK_NUR_INFO)->EnableWindow(currentAeUser.IsOnlyInfo());
    GetDlgItem(IDC_CHECK_RESERVE_CHARGE)->EnableWindow(currentAeUser.IsPflegeReserveCharge());
    GetDlgItem(IDC_CHECK_CHANGE_REBATE_CALC)->EnableWindow(currentAeUser.IsChangeRebateCalc());
    GetDlgItem(IDC_CHECK_DPODAYS)->EnableWindow(currentAeUser.IsChangeDPODays());
    GetDlgItem(IDC_AE_MSV3_BEARB)->EnableWindow(currentAeUser.IsMSV3bearb());

    m_CBOriginTypeSettings.EnableWindow(currentAeUser.IsPflegeOrigintypesettings());

    GetDlgItem(IDC_CHECK_CREMA_MAIL_ADR)->EnableWindow(currentAeUser.IsPflegeCremaMailAdr());
    GetDlgItem(IDC_CHECK_CREMA_STORNO)->EnableWindow(currentAeUser.IsStornoCremaOrder());
    GetDlgItem(IDC_AE_MSV3_BEARB_NO)->EnableWindow(currentAeUser.IsMSV3bearbNo());
    GetDlgItem(IDC_CHECK_2ND_LEVEL)->EnableWindow(currentAeUser.Is2ndLevel());
    GetDlgItem(IDC_CHECK_CB_REMARKS)->EnableWindow(currentAeUser.IsPflegeCBRemarks());
    GetDlgItem(IDC_CHECK_CST_TOURS)->EnableWindow(currentAeUser.IsPflegeCstTours());
    GetDlgItem(IDC_CHECK_EXTRA_TOUR_REASONS)->EnableWindow(currentAeUser.IsPflegeExtraTourReasons());
    GetDlgItem(IDC_CHECK_BESTELL_FENSTER)->EnableWindow(currentAeUser.IsPflegeBestellFenster());
    GetDlgItem(IDC_CHECK_CREMA_CHANGE_TOUR)->EnableWindow(currentAeUser.IsCremaChangeTour());
    GetDlgItem(IDC_CHECK_RESERVATION_CONFIG)->EnableWindow(currentAeUser.IsPflegeReservationConfig());

    m_CBCSVFormate.EnableWindow(currentAeUser.IsPflegeCSVImportParam());
    m_CBCSVImport.EnableWindow(currentAeUser.IsCSVImport());
    m_CBDEGetter.EnableWindow(currentAeUser.IsDEGetter());
    m_CBAnzLief.EnableWindow(currentAeUser.IsAnzLief());
    m_CBAnzRech.EnableWindow(currentAeUser.IsAnzRech());
    m_CBWerbeFach.EnableWindow(currentAeUser.IsEnableWerbeFach());
    m_CBAnzParamChange.EnableWindow(currentAeUser.IsShowParamChanges());

    GetDlgItem(IDC_AE_CMI_BEARBEITEN)->EnableWindow(currentAeUser.IsAbleToChangeCMIOrder());  //TODO DZ

    if (!m_bHiPath)
    {
        GetDlgItem(IDC_STATIC_AGENTID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_AGENTID)->ShowWindow(SW_HIDE);
    }

    if (!AeGetApp()->IsMK())
    {
        GetDlgItem(IDC_CHECK_DPODAYS)->ShowWindow(SW_HIDE);
    }

    UpdateData(FALSE);    // Daten schreiben auf Window

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDRechteAa::OnOK()
{
    UpdateData(TRUE);    // Daten lesen von Window

    if (!m_CVergUser.IsEmpty())
    {
        RechteVorbelegen();
        return;
    }

    // Rechte setzen wie eingegeben
    m_User.SetIsAdminAndereFiliale(m_bAdmin);
    m_User.SetIsErfasAndereFiliale(m_bAndFil);
    m_User.SetIsErwKndInfo(m_bKndInf);
    m_User.SetUpdParAuftrArt(m_bParAufArt);
    m_User.SetParAufBearb(m_bParAufBearb);
    m_User.SetParAufBeErg(m_bParAufErg);
    m_User.SetUpdParBuchArt(m_bParBuchArt);
    m_User.SetParKaBaKomb(m_bParKaBaKomb);
    m_User.SetUpdParKomBehTyp(m_bParKoBehTyp);
    m_User.SetParKommi(m_bParKommi);
    m_User.SetUpdParKommArt(m_bParKommiArt);
    m_User.SetParKondGr(m_bParKondGr);
    m_User.SetUpdParNachrArten(m_bParNachArt);
    m_User.SetUpdUser(m_bUpdUser);
    m_User.SetUpdTour(m_bUpdTour);
    m_User.SetIsAeUser(m_bUser);
    m_User.SetUpdInfo(m_bUpdInfo);
    m_User.SetUpdAltfil(m_bUpdAltfil);
    m_User.SetUpdZeitart(m_bUpdZeitart);
    m_User.SetUpdEntsperr(m_bUpdEntsperr);
    m_User.SetUpdRufpAbw(m_bRufpAbw);
    m_User.SetUpdKndAufArt(m_bKndAart);
    m_User.SetAnzFilialUms(m_bKndFiliUms);
    m_User.SetPlanteil(m_bPlanteil);
    m_User.SetUpdCallback(m_bCallback);
    m_User.SetChangeFiliale(m_bChangeFiliale);
    m_User.SetStatusErl(m_bStatusErl);
    m_User.SetUpdSeraPlan(m_bSeraPlan);
    m_User.SetIsAnzAuf(m_bAufAnz);
    m_User.SetIsSperreAe(m_bSperreAe);
    m_User.SetIsInfoListe(m_bNurInfo);
    m_User.SetUpdMailUser(m_bMailUser);
    m_User.SetIsMessage(m_bMessage);
    m_User.SetUpdModem(m_bUpdModem);
    m_User.SetIsMehrVz(m_bMehrVz);
    m_User.SetAnrufplanuebernahme(m_bAnrufplan);
    m_User.SetRegionenverwalten(m_bUpdRegion);
    m_User.SetFeiertage(m_bFeiertage);
    m_User.SetBewegungen(m_bBewegungen);
    m_User.SetKeinPlan(m_bKeinPlan);
    m_User.SetDispoBearb(m_bDispobearb);
    m_User.SetDispoRechte(m_bDisporechte);
    m_User.SetDispoDoku(m_bDispodoku);
    m_User.SetDispoHinttext(m_bDispoHinttext);
    m_User.SetHiPathUser(m_bHiPath);
    m_User.SetInfoPflege(m_bInfoPflege);
    m_User.SetVorausPflege(m_bVoraus);
    m_User.SetKreditAbschluss(m_bKreditAbschluss);
    m_User.SetInternetAbschluss(m_bInternetAbschluss);
    m_User.SetPflegeReserve(m_bReserve);
    m_User.SetAbschlussBTM(m_bBTMAbschluss);
    m_User.SetAdminCustGrps(m_bCustGrpsAdmin);
    m_User.SetPflegeNotfall(m_bNotfall);
    m_User.SetPflegeCountry(m_bCC);
    m_User.SetPflegeRufweiter(m_bRufweiter);
    m_User.SetPflegeQuota(m_bQuota);
    m_User.SetPflegeDD(m_bDD);
    m_User.SetPflegeBranchInfo(m_bBranchInfo);
    m_User.SetPflegeForbidden(m_bForbidden);
    m_User.SetPflegeSeparat(m_bSeporder);
    m_User.SetPflegeVAIdf(m_bVA);
    m_User.SetFreePrice(m_bFreePrice);
    m_User.SetDiscountUp(m_bDiscountUp);
    m_User.SetBeilageUp(m_bBeilageUp);
    m_User.SetPflegeReserveZert(m_bReserveZert);
    m_User.SetPflegeReserveBPZ(m_bReserveBPZ);
    m_User.SetEinzelhandelApo(m_bArzneiEH);
    m_User.SetCheckPickingChange(m_bCheckKC);
    m_User.SetUserInfoVz(m_bUserInfoVz);
    m_User.SetUserInfoAll(m_bUserInfoAll);
    m_User.SetDealerInfoAll(m_bDealerInfoAll);
    m_User.SetPflegeEncloser(m_bEncloser);
    m_User.SetOnlyInfo(m_bOnlyInfo);
    m_User.SetPflegeReserveCharge(m_bReserveCharge);
    m_User.SetChangeRebateCalc(m_bChangeRebateCalc);
    m_User.SetChangeDPODays(m_bDPODays);
    m_User.SetMSV3bearb(m_bMSV3bearb);
    m_User.SetPflegeOrigintypesettings(m_bOriginTypeSettings);
    m_User.SetPflegeCremaMailAdr(m_bCremaMailAdr);
    m_User.SetStornoCremaOrder(m_bCremaStorno);
    m_User.SetMSV3bearbNo(m_bMSV3bearbNo);
    m_User.Set2ndLevel(m_b2ndLevel);
    m_User.SetPflegeCBRemarks(m_bCBRemarks);
    m_User.SetPflegeCstTours(m_bCstTours);
    m_User.SetPflegeExtraTourReasons(m_bExtraTourReasons);
    m_User.SetPflegeBestellFenster(m_bBestellFenster);
    m_User.SetCremaChangeTour(m_bCremaChangeTour);
    m_User.SetPflegeReservationConfig(m_bReservationConfig);
    m_User.SetPflegeCSVImportParam(m_bCSVFormate);
    m_User.SetCSVImport(m_bCSVImport);
    m_User.SetDEGetter(m_bDEGetter);
    m_User.SetAnzLief(m_bAnzLief);
    m_User.SetAnzRech(m_bAnzRech);
    m_User.SetEnableWerbeFach(m_bWerbeFach);
    m_User.SetShowParamChanges(m_bAnzParamChange);
    m_User.SetAbleToChangeCMIOrder(m_bChangeCMIOrder);
    m_User.SetAgentId(m_csAgentId);
    m_User.SetPoolID(static_cast<short>(m_CComboBoxPool.GetCurSel()));
    m_User.UpdateUserDB();
    CDialogMultiLang::OnOK();
}

void CDRechteAa::RechteVorbelegen()
{
    CAeUser aeUser;
    CAeUser& currentAeUser = GetAeUser();  //aktueller User

    if (!aeUser.InitUser(m_CVergUser, TRUE))
    {
        return;
    }

    //... nicht mehr als die eigenen rechte vergeben
    if (currentAeUser.IsAdminAndereFiliale())
    {
        m_bAdmin = aeUser.IsAdminAndereFiliale();
    }
    if (currentAeUser.IsErfasAndereFiliale())
    {
        m_bAndFil = aeUser.IsErfasAndereFiliale();
    }
    if (currentAeUser.IsErwKndInfo())
    {
        m_bKndInf = aeUser.IsErwKndInfo();
    }
    if (currentAeUser.UpdParAuftrArt())
    {
        m_bParAufArt = aeUser.UpdParAuftrArt();
    }
    if (currentAeUser.UpdParAufBearb())
    {
        m_bParAufBearb = aeUser.UpdParAufBearb();
    }
    if (currentAeUser.UpdParAufBeErg())
    {
        m_bParAufErg = aeUser.UpdParAufBeErg();
    }
    if (currentAeUser.UpdParBuchArt())
    {
        m_bParBuchArt = aeUser.UpdParBuchArt();
    }
    if (currentAeUser.UpdParKaBaKomb())
    {
        m_bParKaBaKomb = aeUser.UpdParKaBaKomb();
    }
    if (currentAeUser.UpdParKomBehTyp())
    {
        m_bParKoBehTyp = aeUser.UpdParKomBehTyp();
    }
    if (currentAeUser.UpdParKommi())
    {
        m_bParKommi = aeUser.UpdParKommi();
    }
    if (currentAeUser.UpdParKommArt())
    {
        m_bParKommiArt = aeUser.UpdParKommArt();
    }
    if (currentAeUser.UpdParKondGr())
    {
        m_bParKondGr = aeUser.UpdParKondGr();
    }
    if (currentAeUser.UpdParNachrArten())
    {
        m_bParNachArt = aeUser.UpdParNachrArten();
    }
    if (currentAeUser.UpdUser())
    {
        m_bUpdUser = aeUser.UpdUser();
    }
    if (currentAeUser.UpdTour())
    {
        m_bUpdTour = aeUser.UpdTour();
    }
    if (currentAeUser.IsAeUser())
    {
        m_bUser = aeUser.IsAeUser();
    }
    if (currentAeUser.UpdInfo())
    {
        m_bUpdInfo = aeUser.UpdInfo();
    }
    if (currentAeUser.UpdAltfil())
    {
        m_bUpdAltfil = aeUser.UpdAltfil();
    }
    if (currentAeUser.UpdZeitart())
    {
        m_bUpdZeitart = aeUser.UpdZeitart();
    }
    if (currentAeUser.UpdEntsperr())
    {
        m_bUpdEntsperr = aeUser.UpdEntsperr();
    }
    if (currentAeUser.UpdRufpAbw())
    {
        m_bRufpAbw = aeUser.UpdRufpAbw();
    }
    if (currentAeUser.UpdKndAufArt())
    {
        m_bKndAart = aeUser.UpdKndAufArt();
    }
    if (currentAeUser.AnzFilialUms())
    {
        m_bKndFiliUms = aeUser.AnzFilialUms();
    }
    if (currentAeUser.Planteil())
    {
        m_bPlanteil = aeUser.Planteil();
    }
    if (currentAeUser.UpdCallback())
    {
        m_bCallback = aeUser.UpdCallback();
    }
    if (currentAeUser.ChangeFiliale())
    {
        m_bChangeFiliale = aeUser.ChangeFiliale();
    }
    if (currentAeUser.StatusErl())
    {
        m_bStatusErl = aeUser.StatusErl();
    }
    if (currentAeUser.UpdSeraPlan())
    {
        m_bSeraPlan = aeUser.UpdSeraPlan();
    }
    if (currentAeUser.IsAnzAuf())
    {
        m_bAufAnz = aeUser.IsAnzAuf();
    }
    if (currentAeUser.IsSperreAe())
    {
        m_bSperreAe = aeUser.IsSperreAe();
    }
    if (currentAeUser.IsInfoListe())
    {
        m_bNurInfo = aeUser.IsInfoListe();
    }
    if (currentAeUser.UpdMailUser())
    {
        m_bMailUser = aeUser.UpdMailUser();
    }
    if (currentAeUser.IsMessage())
    {
        m_bMessage = aeUser.IsMessage();
    }
    if (currentAeUser.UpdModem())
    {
        m_bUpdModem = aeUser.UpdModem();
    }
    if (currentAeUser.IsMehrVz())
    {
        m_bMehrVz = aeUser.IsMehrVz();
    }
    if (currentAeUser.Anrufplanuebernahme())
    {
        m_bAnrufplan = aeUser.Anrufplanuebernahme();
    }
    if (currentAeUser.Regionenverwalten())
    {
        m_bUpdRegion = aeUser.Regionenverwalten();
    }
    if (currentAeUser.Feiertage())
    {
        m_bFeiertage = aeUser.Feiertage();
    }
    if (currentAeUser.Bewegungen())
    {
        m_bBewegungen = aeUser.Bewegungen();
    }
    if (currentAeUser.KeinPlan())
    {
        m_bKeinPlan = aeUser.KeinPlan();
    }
    if (currentAeUser.DispoBearb())
    {
        m_bDispobearb = aeUser.DispoBearb();
    }
    if (currentAeUser.DispoRechte())
    {
        m_bDisporechte = aeUser.DispoRechte();
    }
    if (currentAeUser.DispoDoku())
    {
        m_bDispodoku = aeUser.DispoDoku();
    }
    if (currentAeUser.DispoHinttext())
    {
        m_bDispoHinttext = aeUser.DispoHinttext();
    }
    if (currentAeUser.IsHiPathUser())
    {
        m_bHiPath = aeUser.IsHiPathUser();
    }
    if (currentAeUser.IsInfoPflege())
    {
        m_bInfoPflege = aeUser.IsInfoPflege();
    }
    if (currentAeUser.IsVorausPflege())
    {
        m_bVoraus = aeUser.IsVorausPflege();
    }
    if (currentAeUser.IsKreditAbschluss())
    {
        m_bKreditAbschluss = aeUser.IsKreditAbschluss();
    }
    if (currentAeUser.IsInternetAbschluss())
    {
        m_bInternetAbschluss = aeUser.IsInternetAbschluss();
    }
    if (currentAeUser.IsPflegeReserve())
    {
        m_bReserve = aeUser.IsPflegeReserve();
    }
    if (currentAeUser.IsAbschlussBTM())
    {
        m_bBTMAbschluss = aeUser.IsAbschlussBTM();
    }
    if (currentAeUser.IsAdminCustGrps())
    {
        m_bCustGrpsAdmin = aeUser.IsAdminCustGrps();
    }
    if (currentAeUser.IsPflegeNotfall())
    {
        m_bNotfall = aeUser.IsPflegeNotfall();
    }
    if (currentAeUser.IsPflegeCountry())
    {
        m_bCC = aeUser.IsPflegeCountry();
    }
    if (currentAeUser.IsPflegeRufweiter())
    {
        m_bRufweiter = aeUser.IsPflegeRufweiter();
    }
    if (currentAeUser.IsPflegeQuota())
    {
        m_bQuota = aeUser.IsPflegeQuota();
    }
    if (currentAeUser.IsPflegeDD())
    {
        m_bDD = aeUser.IsPflegeDD();
    }
    if (currentAeUser.IsPflegeBranchInfo())
    {
        m_bBranchInfo = aeUser.IsPflegeBranchInfo();
    }
    if (currentAeUser.IsPflegeForbidden())
    {
        m_bForbidden = aeUser.IsPflegeForbidden();
    }
    if (currentAeUser.IsPflegeSeparat())
    {
        m_bSeporder = aeUser.IsPflegeSeparat();
    }
    if (currentAeUser.IsPflegeVAIdf())
    {
        m_bVA = aeUser.IsPflegeVAIdf();
    }
    if (currentAeUser.IsFreePrice())
    {
        m_bFreePrice = aeUser.IsFreePrice();
    }
    if (currentAeUser.IsDiscountUp())
    {
        m_bDiscountUp = aeUser.IsDiscountUp();
    }
    if (currentAeUser.IsBeilageUp())
    {
        m_bBeilageUp = aeUser.IsBeilageUp();
    }
    if (currentAeUser.IsPflegeReserveZert())
    {
        m_bReserveZert = aeUser.IsPflegeReserveZert();
    }
    if (currentAeUser.IsPflegeReserveBPZ())
    {
        m_bReserveBPZ = aeUser.IsPflegeReserveBPZ();
    }
    if (currentAeUser.IsEinzelhandelApo())
    {
        m_bArzneiEH = aeUser.IsEinzelhandelApo();
    }
    if (currentAeUser.IsCheckPickingChange())
    {
        m_bCheckKC = aeUser.IsCheckPickingChange();
    }
    if (currentAeUser.IsUserInfoVz())
    {
        m_bUserInfoVz = aeUser.IsUserInfoVz();
    }
    if (currentAeUser.IsUserInfoAll())
    {
        m_bUserInfoAll = aeUser.IsUserInfoAll();
    }
    if (currentAeUser.IsDealerInfoAll())
    {
        m_bDealerInfoAll = aeUser.IsDealerInfoAll();
    }
    if (currentAeUser.IsPflegeEncloser())
    {
        m_bEncloser = aeUser.IsPflegeEncloser();
    }
    if (currentAeUser.IsOnlyInfo())
    {
        m_bOnlyInfo = aeUser.IsOnlyInfo();
    }
    if (currentAeUser.IsPflegeReserveCharge())
    {
        m_bReserveCharge = aeUser.IsPflegeReserveCharge();
    }
    if (currentAeUser.IsChangeRebateCalc())
    {
        m_bChangeRebateCalc = aeUser.IsChangeRebateCalc();
    }
    if (currentAeUser.IsChangeDPODays())
    {
        m_bDPODays = aeUser.IsChangeDPODays();
    }
    if (currentAeUser.IsMSV3bearb())
    {
        m_bMSV3bearb = aeUser.IsMSV3bearb();
    }
    if (currentAeUser.IsPflegeOrigintypesettings())
    {
        m_bOriginTypeSettings = aeUser.IsPflegeOrigintypesettings();
    }
    if (currentAeUser.IsPflegeCremaMailAdr())
    {
        m_bCremaMailAdr = aeUser.IsPflegeCremaMailAdr();
    }
    if (currentAeUser.IsStornoCremaOrder())
    {
        m_bCremaStorno = aeUser.IsStornoCremaOrder();
    }
    if (currentAeUser.IsMSV3bearbNo())
    {
        m_bMSV3bearbNo = aeUser.IsMSV3bearbNo();
    }
    if (currentAeUser.Is2ndLevel())
    {
        m_b2ndLevel = aeUser.Is2ndLevel();
    }
    if (currentAeUser.IsPflegeCBRemarks())
    {
        m_bCBRemarks = aeUser.IsPflegeCBRemarks();
    }
    if (currentAeUser.IsPflegeCstTours())
    {
        m_bCstTours = aeUser.IsPflegeCstTours();
    }
    if (currentAeUser.IsPflegeExtraTourReasons())
    {
        m_bExtraTourReasons = aeUser.IsPflegeExtraTourReasons();
    }
    if (currentAeUser.IsPflegeBestellFenster())
    {
        m_bBestellFenster = aeUser.IsPflegeBestellFenster();
    }
    if (currentAeUser.IsCremaChangeTour())
    {
        m_bCremaChangeTour = aeUser.IsCremaChangeTour();
    }
    if (currentAeUser.IsPflegeReservationConfig())
    {
        m_bReservationConfig = aeUser.IsPflegeReservationConfig();
    }
    if (currentAeUser.IsPflegeCSVImportParam())
    {
        m_bCSVFormate = aeUser.IsPflegeCSVImportParam();
    }
    if (currentAeUser.IsCSVImport())
    {
        m_bCSVImport = aeUser.IsCSVImport();
    }
    if (currentAeUser.IsDEGetter())
    {
        m_bDEGetter = aeUser.IsDEGetter();
    }
    if (currentAeUser.IsAnzLief())
    {
        m_bAnzLief = aeUser.IsAnzLief();
    }
    if (currentAeUser.IsAnzRech())
    {
        m_bAnzRech = aeUser.IsAnzRech();
    }
    if (currentAeUser.IsEnableWerbeFach())
    {
        m_bWerbeFach = aeUser.IsEnableWerbeFach();
    }
    if (currentAeUser.IsShowParamChanges())
    {
        m_bAnzParamChange = aeUser.IsShowParamChanges();
    }
    if (currentAeUser.IsAbleToChangeCMIOrder()) //TODO DZ
    {
        m_bChangeCMIOrder = aeUser.IsAbleToChangeCMIOrder();
    }

    m_CVergUser = "";
    UpdateData(FALSE);    // Daten schreiben auf Window
}

void CDRechteAa::OnAeAdmin()
{
}

void CDRechteAa::OnAeAndereFiliale()
{
}

void CDRechteAa::OnAeKundeninfo()
{
}

void CDRechteAa::OnAeParAufart()
{
}

void CDRechteAa::OnAeParAufbearb()
{
}

void CDRechteAa::OnAeParAuferg()
{
}

void CDRechteAa::OnAeParBuchart()
{
}

void CDRechteAa::OnAeParKabakomb()
{
}

void CDRechteAa::OnAeParKobehtyp()
{
}

void CDRechteAa::OnAeParKommi()
{
}

void CDRechteAa::OnAeParKommiart()
{
}

void CDRechteAa::OnAeParKondgr()
{
}

void CDRechteAa::OnAeParNachart()
{
}

void CDRechteAa::OnAeUpduser()
{
}

void CDRechteAa::OnAeUser()
{
}

void CDRechteAa::OnAeUpdinfo()
{
}

void CDRechteAa::OnAeZeitart()
{
}

void CDRechteAa::OnAeAltfiliale()
{
}

void CDRechteAa::OnAeEntsperr()
{
}

void CDRechteAa::OnAeRufpAbw()
{
}

void CDRechteAa::OnAeKndAart()
{
}

void CDRechteAa::OnAeKndFiliUms()
{
}

void CDRechteAa::OnAePlanteil()
{
}

void CDRechteAa::OnAeCallback()
{
}

void CDRechteAa::OnCheckChangeFiliale()
{
}

void CDRechteAa::OnAeStatusErl()
{
}

void CDRechteAa::OnAeSeraPlan()
{
}

void CDRechteAa::OnAeAufAnz()
{
}

void CDRechteAa::OnAeSperreAe()
{
}

void CDRechteAa::OnAeNurInfo()
{
}

void CDRechteAa::OnCheckMailUser()
{
}

void CDRechteAa::OnCheckMessage()
{
}

void CDRechteAa::OnAeUpdModem()
{
}

void CDRechteAa::OnAeMehrVz()
{
}

void CDRechteAa::OnAeAnrufplan()
{
}

void CDRechteAa::OnAeUpdRegion()
{
}

void CDRechteAa::OnAeFeiertage()
{
}

void CDRechteAa::OnAeBewegungen()
{
}

void CDRechteAa::OnCheckKeinPlan()
{
}

void CDRechteAa::OnAeDispoBearb()
{
}

void CDRechteAa::OnAeDispoRechte()
{
}

void CDRechteAa::OnAeDispoDoku()
{
}

void CDRechteAa::OnAeHipath()
{
    if (m_CBHiPath.GetCheck())
    {
        GetDlgItem(IDC_STATIC_AGENTID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_AGENTID)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_AGENTID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_AGENTID)->ShowWindow(SW_SHOW);
    }
}

void CDRechteAa::OnChangeEditAgentid()
{
    AllgLaengeKontr(&m_edit_AgentId, L_AEPWD_AGENTID, AeGetApp()->Modus());
}

void CDRechteAa::OnCheckInfoPflege()
{
}

void CDRechteAa::OnBnClickedAeVoraus()
{
}

void CDRechteAa::OnBnClickedAeKreditAbschluss()
{
}

void CDRechteAa::OnBnClickedAeInternetAbschluss()
{
}

void CDRechteAa::OnBnClickedAeReserve()
{
}

void CDRechteAa::OnBnClickedAeBtmAbschluss()
{
}
//------------------------------------------------------------------------------------------------//
//
//------------------------------------------------------------------------------------------------//
void CDRechteAa::OnBnClickedChkCustgrps4collorder()
{
}

void CDRechteAa::OnBnClickedCheckNotfall()
{
}

void CDRechteAa::OnBnClickedCheckCountry()
{
}

void CDRechteAa::OnBnClickedCheckRufweiter()
{
}

void CDRechteAa::OnBnClickedCheckQuota()
{
}

void CDRechteAa::OnBnClickedCheckDd()
{
}

void CDRechteAa::OnBnClickedCheckBranchinfo()
{
}

void CDRechteAa::OnBnClickedCheckForbidden()
{
}

void CDRechteAa::OnBnClickedCheckSeporder()
{
}

void CDRechteAa::OnBnClickedCheckVa()
{
}

void CDRechteAa::OnBnClickedCheckFreePrice()
{
}

void CDRechteAa::OnBnClickedCheckDiscountUp()
{
}

void CDRechteAa::OnBnClickedCheckBeilageUp()
{
}

void CDRechteAa::OnBnClickedAeReserveZert()
{
}

void CDRechteAa::OnBnClickedAeReserveBPZ()
{
}

void CDRechteAa::OnBnClickedArzneiEH()
{
}

void CDRechteAa::OnBnClickedCheckKC()
{
}

void CDRechteAa::OnBnClickedUserInfoVz()
{
}

void CDRechteAa::OnBnClickedUserInfoAll()
{
}

void CDRechteAa::OnBnClickedCheckDealerInfoAlle()
{
}

void CDRechteAa::OnBnClickedCheckEncloser()
{
}

void CDRechteAa::OnBnClickedCheckNurInfo()
{
}

void CDRechteAa::OnBnClickedCheckReserveCharge()
{
}

void CDRechteAa::OnBnClickedCheckChangeRebateCalc()
{
}

void CDRechteAa::OnBnClickedCheckDpodays()
{
}

void CDRechteAa::OnBnClickedAeMsv3Bearb()
{
}

void CDRechteAa::OnBnClickedCheckOrigintypesettings()
{
}

void CDRechteAa::OnBnClickedCheckCremaMailAdr()
{
}

void CDRechteAa::OnBnClickedCheckCremaStorno()
{
}


void CDRechteAa::OnBnClickedAeMsv3BearbNo()
{
}

void CDRechteAa::OnBnClickedCheck2ndLevel()
{
}

void CDRechteAa::OnBnClickedCBRemarks()
{
}

void CDRechteAa::OnBnClickedCstTours()
{
}

void CDRechteAa::OnBnClickedExtraTourReasons()
{
}

void CDRechteAa::OnBnClickedBestellFenster()
{
}

void CDRechteAa::OnBnClickedCremaChangeTour()
{
}

void CDRechteAa::OnBnClickedCheckReservationConfig()
{
}

void CDRechteAa::OnBnClickedCheckPflegeCsvimport()
{
}

void CDRechteAa::OnBnClickedCheckImportCsvAuftrag()
{
}

void CDRechteAa::OnBnClickedCheckDeGetter()
{
}

void CDRechteAa::OnBnClickedCheckAnzLief()
{
}

void CDRechteAa::OnBnClickedCheckAnzRech()
{
}

void CDRechteAa::OnBnClickedAeParWerbefach()
{
}

void CDRechteAa::OnBnClickedCheckAnzParamChanges()
{
}

void CDRechteAa::OnBnClickedChangeCMIOrder()
{
}
